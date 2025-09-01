#include "../lib/MessageHandler.h"
#include "../lib/ServerManager.h"
#include "message.pb.h"

MessageHandler::MessageHandler(ServerManager* manager) {
    serverManager = manager;
    isRunning.store(true);
    handleClientMsgThread = std::thread(&MessageHandler::ProcessClientMessage, this);
}

MessageHandler::~MessageHandler() {
    isRunning.store(false);
    if(handleClientMsgThread.joinable()) handleClientMsgThread.join();
}

void MessageHandler::ProcessClientMessage()  {
    while(isRunning) {
        std::string message;
        std::unique_lock<std::mutex> lck(handleClientMsgMutex);
        ClientMsgCv.wait(lck, [this]{return isRunning.load() == false || !msgFromClientQueue.empty();});

        if(!isRunning.load())   continue;
        message = msgFromClientQueue.front();
        msgFromClientQueue.pop();
        lck.unlock();

        PacketMessage packetMessage;
        if (packetMessage.ParseFromString(message)) {
            switch (packetMessage.payload_case()) {
                case PacketMessage::kNormalMsg: {
                    const ChatMessage& msg = packetMessage.normal_msg();
                    serverManager->AddBroadCastMessage(msg.user_id(), message);
                    break;
                }
                case PacketMessage::kCommandMsg: {
                    const CommandMessage& cmd = packetMessage.command_msg();
                    // TODO handll command here
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

int MessageHandler::AddToClientQueue(const std::string& message) {
    std::unique_lock<std::mutex> lck(handleClientMsgMutex);
    msgFromClientQueue.push(message);
    ClientMsgCv.notify_one();
    return 0;
}

int MessageHandler::BuildSetIdRequest(const int& id, std::string& output) {
    PacketMessage packetMessage;
    CommandMessage* cmdMessage = packetMessage.mutable_command_msg();
    cmdMessage->set_command(CommandMessage::SET_USER_ID);
    SetUserIdMessage* setUserId = cmdMessage->mutable_setuserid();
    setUserId->set_user_id(id);
    if (packetMessage.SerializeToString(&output)) {
        return 0;
    }
    return 1;
} 