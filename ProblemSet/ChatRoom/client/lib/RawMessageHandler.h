#include "Messagehandler.h"


class RawMessageHandler : public MessageHandler {
    private:

    public:
        RawMessageHandler() {
            type = MessageHandlerType::RAW;
        }
        int decode(const std::string& input, std::string& output){
            output = input;
            return 0;
        }

        int encode(const std::string& input, std::string& output){
            output = input;
            return 0;
        }
};