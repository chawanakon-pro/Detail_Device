# Check Storage Device

This program is used to display details about every storage device on the system. It provides the following information:

- Path to the device.
- Total capacity of the device.
- Unused capacity remaining on the device.
- Percentage of used and unused space.

## Build and Run Instructions

This program is designed to run on **Ubuntu 24.04**. To build and execute the program, follow these steps:

### **Dependencies**

Ensure you have the following installed:

- GCC (GNU Compiler Collection)
- Standard C libraries

To install GCC, run:

```sh
sudo apt update && sudo apt install gcc -y
```

### **Building the Program**

Compile the program using:

```sh
gcc check_storage_device.c -o check_storage_device
```

### **Running the Program**

Execute the compiled binary:

```sh
./check_storage_device
```

This will output storage details in the terminal.

## **Approach and Testing**

The program retrieves storage information by reading the system's mounted file systems using `/etc/mtab`. It uses the `statvfs` system call to gather storage statistics such as total size, available space, and usage percentages.

For testing, the program was executed on **Ubuntu 24.04.2** using multiple mounted storage devices, ensuring that it correctly reports different filesystem sizes and usage percentages. Error handling is included to manage cases where a filesystem cannot be accessed.

This implementation is efficient, as it reads system mount points dynamically and presents real-time storage information in an easy-to-read format.

