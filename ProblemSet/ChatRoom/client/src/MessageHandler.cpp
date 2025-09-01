#include "../lib/MessageHandler.h"
#include "../lib/ClientManager.h"
#include "../lib/Transmission.h"
#include "../lib/Log.h"

#include "message.pb.h"

MessageHandler::MessageHandler(ClientManager* manager){
    clientManager = manager;
    isRunning.store(true);
    handleServerMsgThread = std::thread(&MessageHandler::processServerMessage, this);
    handleConsoleMsgThread = std::thread(&MessageHandler::processConsoleMessage, this);
}

MessageHandler::~MessageHandler() {
    isRunning.store(false);
    if(handleServerMsgThread.joinable()) handleServerMsgThread.join();
    if(handleConsoleMsgThread.joinable()) handleConsoleMsgThread.join();
}

void MessageHandler::processServerMessage() {
    while(isRunning) {
        std::string message;
        std::unique_lock<std::mutex> lck(handleServerMsgMutex);
        ServerMsgCv.wait(lck, [this]{return isRunning.load() == false || !msgFromServerQueue.empty();});

        if(!isRunning.load())   continue;
        message = msgFromServerQueue.front();
        msgFromServerQueue.pop();
        lck.unlock();

        PacketMessage packetMessage;
        if (packetMessage.ParseFromString(message)) {
            switch (packetMessage.payload_case()) {
                case PacketMessage::kNormalMsg: {
                    const ChatMessage& msg = packetMessage.normal_msg();
                    LOG_MSG(msg.user_id(), msg.content());
                    break;
                }
                case PacketMessage::kCommandMsg: {
                    const CommandMessage& cmd = packetMessage.command_msg();
                    // TODO handle command here
                    switch (cmd.command()) {
                        case CommandMessage::SET_USER_ID:
                            clientManager->SetId( cmd.setuserid().user_id());
                            break;
                        default:
                            LOG("Unknown command");
                    }
                    break;
                }
                case PacketMessage::PAYLOAD_NOT_SET: {
                    continue;
                }
            }
        } else {
            std::cerr << "Failed to parse message." << std::endl;
        }
    }
}

void MessageHandler::processConsoleMessage() {
    while(isRunning) {
        std::string message;
        std::unique_lock<std::mutex> lck(handleConsoleMsgMutex);
        ConsoleMsgCv.wait(lck, [this]{return isRunning.load() == false || !msgFromConsoleQueue.empty();});

        if(!isRunning.load())   continue;
        message = msgFromConsoleQueue.front();
        msgFromConsoleQueue.pop();
        lck.unlock();

        if(message[0] == '/') {
            // TODO: Add handle command here
        }
        else {
            // Chat message
            PacketMessage packetMessage;
            ChatMessage* chatMessage = packetMessage.mutable_normal_msg();
            chatMessage->set_user_id(clientManager->GetId());
            chatMessage->set_content(message);
            std::string builtMessage;
            if (packetMessage.SerializeToString(&builtMessage)) {
                // TODO: put to server queue to send
                Transmission* transmission = clientManager->GetTransmission();
                if(transmission != nullptr) {
                    transmission->AddSendingMessageToQueue(builtMessage);
                }
                else {
                    // TODO: no server connection
                }
            }
            else {
                // TODO: fail to parse message 
            }
        }
    }
}

int MessageHandler::AddToServerQueue(const std::string& message) {
    {
        std::unique_lock<std::mutex> lck(handleServerMsgMutex);
        msgFromServerQueue.push(message);
        ServerMsgCv.notify_one();
    }
    return 0;
}

int MessageHandler::AddToConsoleQueue(const std::string& message) {
    {
        std::unique_lock<std::mutex> lck(handleConsoleMsgMutex);
        msgFromConsoleQueue.push(message);
        ConsoleMsgCv.notify_one();
    }
    return 0;
}

