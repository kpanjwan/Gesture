#include <iostream>
#include <string.h>
#include <vector>
#include "Leap.h"
#include <iostream>

using namespace Leap;
using namespace std;


class SampleListener : public Listener {
public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);
    
private:
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};
int counter = 1;

void SampleListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
    // Get the most recent frame and report some basic information
    const Frame frame = controller.frame();
    
    for (int i = 0; i < 10; i++) {
        counter++;
        HandList hands = frame.hands();
        for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
            // Get the first hand
            const Hand hand = *hl;
            int array[5], count = 0;
            const FingerList fingers = hand.fingers();
            for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
                const Finger finger = *fl;
                array[count++] = finger.isExtended();
            }
            if ((array[2] && array[3] && array[4] && !array[0] && !array[1]) && counter % 900 == 0) {
                cout << "9  ";
            }
            else if ((array[1] && array[3] && array[4] && !array[0] && !array[2]) && counter % 900 == 0) {
                cout << "8  ";
            }
            else if ((array[1] && array[2] && array[4] && !array[0] && !array[3]) && counter % 900 == 0) {
                cout << "7  ";
            }
            else if ((array[1] && array[2] && array[3] && !array[0] && !array[4]) && counter % 900 == 0) {
                cout << "6  ";
            }
            else if ((array[0] && array[1] && array[2] && array[3] && array[4]) && counter % 900 == 0) {
                cout << "5  ";
            }
            else if ((array[1] && array[2] && array[3] && array[4] && !array[0]) && counter % 900 == 0) {
                cout << "4  ";
            }
            else if ((array[0] && array[1] && array[2] && !array[3] && !array[4]) && counter % 900 == 0) {
                cout << "3  ";
            }
            else if ((array[1] && array[2] && !array[0] && !array[3] && !array[4]) && counter % 900 == 0) {
                cout << "2  ";
            }
            else if ((array[1] && !array[0] && !array[2] && !array[3] && !array[4]) && counter % 900 == 0) {
                cout << "1  ";
            }
            else if ((!array[0] && !array[1] && !array[2] && !array[3] && !array[4]) && counter % 900 == 0){
                cout << "0  ";
            }
            else if (counter % 900 == 0) {
                cout << "Not a number/wrong" << endl;
            }
        }
    }
}

void SampleListener::onFocusGained(const Controller& controller) {
    std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
    std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
    std::cout << "Device Changed" << std::endl;
    const DeviceList devices = controller.devices();
    
    for (int i = 0; i < devices.count(); ++i) {
        std::cout << "id: " << devices[i].toString() << std::endl;
        std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    }
}

void SampleListener::onServiceConnect(const Controller& controller) {
    std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
    std::cout << "Service Disconnected" << std::endl;
}

int main(int argc, char** argv) {
    
    // Create a sample listener and controller
    SampleListener listener;
    Controller controller;
    
    // Have the sample listener receive events from the controller

    controller.addListener(listener);
    
    if (argc > 1 && strcmp(argv[1], "--bg") == 0)
        controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    
    cout << "Print the numbers 9, 5, 8, 1, 0, 2, 3, 6, 4, 7" << endl;
    
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();
    controller.removeListener(listener);
    return 0;
}
