from MegaJoystickHandler import MegaJoystickHandler

if __name__ == '__main__':
    my_joystick = MegaJoystickHandler(1,"COM4", 500000)
    my_joystick.activate()
