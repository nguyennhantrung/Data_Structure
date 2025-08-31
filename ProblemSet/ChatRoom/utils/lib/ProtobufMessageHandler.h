#include "MessageHandler.h"
#include "message.pb.h"

class ProtobufMessageHandler : public MessageHandler {
    private:

    public:
        ProtobufMessageHandler() {
            type = MessageHandlerType::PROTO;
        }
        int decode(const std::string& input, int& id, bool& command, std::string& output){
            ChatMessage chatMessage;
            // cout << "decode message size " << input.length() << " " << input << endl;
            if (chatMessage.ParseFromString(input)) {
                // Access the integer user ID
                id = chatMessage.user_id();
                command = chatMessage.command();
                output = chatMessage.content();
            } else {
                std::cerr << "Failed to parse message." << std::endl;
                return 1;
            }
            return 0;
        }

        int encode(const std::string& input, int id, bool command, std::string& output){
            ChatMessage chat_message;
            chat_message.set_user_id(id);
            chat_message.set_content(input);
            chat_message.set_command(command);
            if (chat_message.SerializeToString(&output)) {
                return 0;
                // std::cout << "Message serialized and ready to send. Size: " << output.length() << " bytes." << std::endl;
            } else {
                return 1;
            }
        }
};