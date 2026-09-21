# DualSense 4-channel AUX routing test

The verified DualSense USB playback format is 48 kHz, 16-bit, four channels. The exact channel pair that feeds the controller 3.5 mm headset must be verified on hardware before PSController enables normal game audio.

PSController therefore starts the router in SILENT mode.

Hardware test:
1. connect DualSense by USB
2. connect headphones to the DualSense 3.5 mm jack
3. verify the USB audio profile/descriptors
4. send a low-level controlled stereo test signal to channel pair 0/1
5. if the headset is silent, stop the stream before testing pair 2/3
6. record which pair reaches the headset
7. keep all unused channels zero

Do not send arbitrary full-volume data to all four channels. Some channels may represent a different physical output path.

Once the correct pair is verified, that result can become the normal DualSense AUX routing profile.
