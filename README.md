# Raspberry Pi Communication API

This API allows multiple Single-Board-Computer (raspberry pi preferred) to communicate with each other.

The following functionalities are available:
- Sending, writing, reading, and executing files.
- Remote control of GPIO pins on other Raspberry Pis (Raspi -> Raspi).
- For intercommunication control, you can log in from one Raspberry Pi to another and distribute permissions.
- Each authorized Raspberry Pi can retrieve files of any type.
- Each Raspberry Pi can send commands to another.

## Code

The project's codebase is located in the `/src` directory, which comprises both server-side and client-side components.

- **Client Side**: In the `/src/client` directory, you can interact with the API, making requests and utilizing its features.

- **Server Side**: The server-side code, constituting the actual API, resides in the `/src/server` directory.

## Documentation

The project's documentation can be found in the `/doc` directory, providing comprehensive information and guidance.

