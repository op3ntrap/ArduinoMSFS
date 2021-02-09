import pyvjoy
from serial import Serial, SerialException
import pyvjoy
import cython
from serial import Serial, SerialException

@cython.cclass
cdef class MegaJoystickHandler:
    """
    JoystickHandler class for Arduino Mega through serial communication.
    """
    cdef:
        int joy_id
        str serial_port
        int serial_baud
        dict switch_dict
        bytes last_payload
        bytes payload


    def __cinit__(self, vjoy_id, s_port, s_baud):
        self.joy_id = vjoy_id
        self.serial_port = s_port
        self.serial_baud = s_baud
        # Since the inputs are all pull_ups we need to reverse/flip
        # the bits. switch_dict uses key/value approach for the flips.
        self.switch_dict = {48: 1, 49: 0}
        self.last_payload = b''  # Store modified previous switch state.
        self.payload = b''

    # @staticmethod
    cpdef void activate(self):
        joystick = pyvjoy.VJoyDevice(self.joy_id)  # initialise the Joystick
        with Serial(port=self.serial_port, baudrate=self.serial_baud) as arduino_serial:

            while True:
                # time.sleep(0.001)
                try:
                    arduino_serial.flushOutput()  # Flush the output
                    self.payload = bytes(arduino_serial.readline().rstrip())  # Prettify the data.
                    # Check for state change and verify the payload is normal
                    if (self.last_payload != self.payload) & (len(self.payload) == 80):
                        for _i in range(80):
                            vjoy_status_output = joystick.set_button(_i + 1, self.switch_dict[self.payload[_i]])
                            del vjoy_status_output
                        self.last_payload = self.payload  # Updating the state variable.

                except (SerialException, KeyError, NameError):  # Blanket exception Handler.
                    self.joystick.reset_buttons()  # Safely reset all the buttons.
                    continue  # Poll for a new serial.read.
