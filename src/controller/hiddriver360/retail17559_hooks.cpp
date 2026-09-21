#include "retail17559_hooks.h"
#include <string.h>
namespace retail17559_hooks {
static HookApi g_api={}; static bool g_installed=false;
static uintptr_t g_targets[5]={0,0,0,0,0};
static const uintptr_t HID_ADD=0x800E4D68u, HID_REMOVE=0x800E4D28u;
static const uint8_t ADD_PREFIX[]={0x7D,0x88,0x02,0xA6};
static const uint8_t REMOVE_PREFIX[]={0x81,0x63};
static bool match(uintptr_t a,const uint8_t* e,size_t n){uint8_t b[8]={}; return g_api.read_memory&&n<=sizeof(b)&&g_api.read_memory(a,b,n)&&memcmp(b,e,n)==0;}
void bind_hook_api(const HookApi& api){g_api=api;}
static void rollback(){if(!g_api.remove_detour)return; for(int i=4;i>=0;--i){if(g_targets[i]){g_api.remove_detour(g_targets[i]);g_targets[i]=0;}}}
bool install(const controller_runtime::ResolvedExports& e,void* ha,void* hr,void* xi,void* xc,void* xs){
 if(g_installed)return true;
 if(!g_api.install_detour||!g_api.read_memory||!ha||!hr||!xi||!xc||!xs)return false;
 if(!e.xinputd_read_state||!e.xam_input_get_capabilities_ex||!e.xam_input_set_state)return false;
 if(!match(HID_ADD,ADD_PREFIX,sizeof(ADD_PREFIX))||!match(HID_REMOVE,REMOVE_PREFIX,sizeof(REMOVE_PREFIX)))return false;
 uintptr_t t[5]={HID_ADD,HID_REMOVE,(uintptr_t)e.xinputd_read_state,(uintptr_t)e.xam_input_get_capabilities_ex,(uintptr_t)e.xam_input_set_state};
 void* hooks[5]={ha,hr,xi,xc,xs};
 for(int i=0;i<5;++i){void* original=0;if(!g_api.install_detour(t[i],hooks[i],&original)){rollback();return false;}g_targets[i]=t[i];}
 g_installed=true; return true;
}
void remove(){rollback();g_installed=false;}
bool installed(){return g_installed;}
}
