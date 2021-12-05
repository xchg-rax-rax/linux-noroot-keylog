#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>



int main(int argc, char** argv) {
    int i, num_devices, screen, key_press_type, key_release_type;
    int ret_vals[3];
    XID id;
    Display* dpy;
    Window root_win;
    XDeviceInfo* devices;
    XDeviceInfo* device_info;
    XDevice* device;
    XEventClass event_classes[1];
    XEvent event;
    XDeviceKeyEvent* key_event;

    if (argc != 2) {
        printf("Usage: %s <id>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (!(id = (XID) strtoul(argv[1], NULL, 10))) {
        printf("Usage: %s <id>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open display
    printf("[*] Opening Default Display...\n");
    if(!(dpy = XOpenDisplay(NULL))) {
        printf("[!] Error: Could not open default display.\n"); 
        exit(EXIT_FAILURE);
    }
    printf("[*] Checking for XInputExtension...\n");
    if (!XQueryExtension(dpy, "XInputExtension", &ret_vals[0], &ret_vals[1], &ret_vals[2])) { // may need those pointers....
        printf("[!] Error: XInputExtension not present.\n"); 
        exit(EXIT_FAILURE);
    }
    
    // Get device 
    printf("[*] Getting device with id %d.\n", id);
    devices = XListInputDevices(dpy, &num_devices);
    for (i = 0; i < num_devices; i++) {
        if (devices[i].id == id)
        {
            printf("[*] Found Device\n");
            device_info = &devices[i];
            break;
        }
    }
    if (i > num_devices) {
        printf("[!] Error: Device with id %d not found.\n", id); 
        exit(EXIT_FAILURE);
    }

    // Get devices 
    screen = DefaultScreen(dpy);
    root_win = RootWindow(dpy, screen);
    device = XOpenDevice(dpy, device_info->id);

    // Hook events
    // imho these macros are stupid, confusing and pure-evil. (Not to mention poorly documented...)
    key_press_type = -1;
    key_release_type = -1;
    DeviceKeyPress(device, key_press_type, event_classes[0]);
    //DeviceKeyRelease(device, key_release_type, event_classes[1]);
    XSelectExtensionEvent(dpy, root_win, event_classes, 1);

    KeySym key_sym;
    // Listen for key board events...
    while(1) {
        XNextEvent(dpy, &event);
        key_event = (XDeviceKeyEvent*) &event;
        key_sym = XkbKeycodeToKeysym(dpy, key_event->keycode, 0, 0);
        printf("Key Pressed : %s\n", XKeysymToString(key_sym));
    }
    exit(EXIT_SUCCESS);
}
