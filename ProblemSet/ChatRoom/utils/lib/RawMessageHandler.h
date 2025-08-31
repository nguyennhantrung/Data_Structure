#include "MessageHandler.h"


class RawMessageHandler : public MessageHandler {
    private:

    public:
        RawMessageHandler() {
            type = MessageHandlerType::RAW;
        }
        int decode(const std::string& input, int& id, bool& command, std::string& output){
            output = input;
            return 0;
        }

        int encode(const std::string& input, int id, bool command, std::string& output){
            output = input;
            return 0;
        }
};