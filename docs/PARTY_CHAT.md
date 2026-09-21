# Xbox 360 dashboard / Xbox Live Party Chat target

PSController's target is the Xbox 360's built-in headset/voice path, not a private voice chat implementation.

Required observable behavior on kernel 17559:
- the signed-in Xbox user sees a headset/voice device
- speaking into a headset connected to DS4/DualSense AUX makes the dashboard/Party Chat microphone activity indicator react
- microphone PCM can enter Xbox Live Party Chat
- incoming Party Chat audio can be routed back to the same controller AUX headset
- disconnecting or failing audio must not break HID controller input or dashboard boot

The new party_chat_bridge is intentionally an adapter boundary. Public information confirms Xbox 360 titles used the XHV2 voice system with XAudio2 underneath, but that does not by itself document a safe global dashboard Party Chat injection API for a DashLaunch plugin. Therefore PSController does not fake this integration or claim Party Chat works yet.

Next implementation requirement:
1. identify a verified kernel/dashboard headset or voice registration path on 17559
2. implement register/unregister for the signed-in user
3. implement the PCM format conversion expected by that path
4. bind aux_capture::deliver to party_chat::on_microphone_pcm
5. route returned chat PCM through aux_session to DS4/DualSense AUX
6. test the dashboard microphone activity indicator before Xbox Live testing

The bridge fails closed: until a verified Xbox voice adapter is installed, STATE_WAITING_FOR_XBOX_VOICE is returned and controller HID remains unaffected.
