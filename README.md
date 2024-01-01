# android-pin-bruteforce

Emulate a usb hid keyboard to pentest vulernable devices using arduino uno rev4 wifi, other arduino hw with this capability should also work.

preq: keyboard library

* sketch_hid_keyboard     - brute force 4 pin with 30s backoff starting at 0000
* sketch_pinbrute_prelist - brute force using a prelist array, e.g. with the 20 most common pins of length 4-10.
