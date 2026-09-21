#pragma once

namespace audio {

enum AuxController { AUX_UNKNOWN = 0, AUX_DS4, AUX_DUALSENSE };

enum OutputRoute {
    OUTPUT_NONE = 0,
    OUTPUT_CONTROLLER_CHAT_ONLY,
    OUTPUT_CONTROLLER_AUX,
    OUTPUT_USB_HEADSET
};

enum MicrophoneRoute {
    MIC_NONE = 0,
    MIC_DUALSENSE_BUILTIN,
    MIC_CONTROLLER_AUX,
    MIC_USB_HEADSET
};

struct OutputPolicy {
    bool game_audio;
    bool party_chat;
    bool game_chat;
};

bool initialize_optional();
void shutdown();
bool is_available();

bool enable_controller_aux(AuxController controller);
void disable_controller_aux();

// Routing priority never changes controller input:
// USB headset > controller AUX > DualSense built-in chat path.
// USB/AUX receive game audio + Party Chat + Game Chat.
// Bare DualSense receives Party Chat + Game Chat only, never game audio.
void set_usb_headset_present(bool present);
void set_inzone_present(bool present); // compatibility alias
void set_controller_connected(bool present);
void set_controller_aux_present(bool present);
void set_controller_is_dualsense(bool dualsense);

OutputRoute active_output();
OutputPolicy active_output_policy();
MicrophoneRoute active_microphone();
bool controller_aux_available();
bool usb_headset_available();
bool inzone_available();

}
