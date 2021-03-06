#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "new_battle_struct.h"
#include "static_references.h"

u8 check_ability(u8 bank, u8 ability);
u8 get_airborne_state(u8 bank, u8 mode, u8 check_levitate);
u16 get_1_16_of_max_hp(u8 bank);
u8 item_battle_effects(u8 switchid, u8 bank, u8 moveturn);

u8 sample_text[] = {0xDD, 0xFF};
u8 snowwarning_text[] = {0xFD, 0x13, 0xB4, 0xE7, 0, 0xFD, 0x1A, 0xFE, 0xEB, 0xDC, 0xDD, 0xE4, 0xE4, 0xD9, 0xD8, 0x00, 0xE9, 0xE4, 0x00, 0xD5, 0x00, 0xDC, 0xD5, 0xDD, 0xE0, 0xE7, 0xE8, 0xE3, 0xE6, 0xE1, 0xAB, 0xFF};
u8 extreme_sun_activation_text[] = {0xCE, 0xDC, 0xD9, 0x00, 0xE7, 0xE9, 0xE2, 0xE0, 0xDD, 0xDB, 0xDC, 0xE8, 0x00, 0xE8, 0xE9, 0xE6, 0xE2, 0xD9, 0xD8, 0xFE, 0xD9, 0xEC, 0xE8, 0xE6, 0xD9, 0xE1, 0xD9, 0xE0, 0xED, 0x00, 0xDC, 0xD5, 0xE6, 0xE7, 0xDC, 0xAB, 0xFF};
u8 heavyrain_activation_text[] = {0xBB, 0x00, 0xDC, 0xD9, 0xD5, 0xEA, 0xED, 0x00, 0xE6, 0xD5, 0xDD, 0xE2, 0x00, 0xD6, 0xD9, 0xDB, 0xD5, 0xE2, 0x00, 0xE8, 0xE3, 0x00, 0xDA, 0xD5, 0xE0, 0xE0, 0xAB, 0xFF};
u8 mysticalaircurrent_activation_text[] = {0xBB, 0x00, 0xE1, 0xED, 0xE7, 0xE8, 0xD9, 0xE6, 0xDD, 0xE3, 0xE9, 0xE7, 0x00, 0xD5, 0xDD, 0xE6, 0x00, 0xD7, 0xE9, 0xE6, 0xE6, 0xD9, 0xE2, 0xE8, 0xFE, 0xDD, 0xE7, 0x00, 0xE4, 0xE6, 0xE3, 0xE8, 0xD9, 0xD7, 0xE8, 0xDD, 0xE2, 0xDB, 0x00, 0xC0, 0xE0, 0xED, 0xDD, 0xE2, 0xDB, 0xAE, 0xE8, 0xED, 0xE4, 0xD9, 0x00, 0xCA, 0xE3, 0xDF, 0x1B, 0xE1, 0xE3, 0xE2, 0xAB, 0xFF};
u8 forewarn_text[] = {0xFD, 0x13, 0xB4, 0xE7, 0, 0xFD, 0x1A, 0xFE, 0xD5, 0xE0, 0xD9, 0xE6, 0xE8, 0xD9, 0xD8, 0, 0xDD, 0xE8, 0, 0xE8, 0xE3, 0x0, 0xFD, 0, 0xAB, 0xFF};
u8 slowstart_text[] = {0xFD, 0x13, 0x0, 0xD7, 0xD5, 0xE2, 0xB4, 0xE8, 0x00, 0xDB, 0xD9, 0xE8, 0x00, 0xDD, 0xE8, 0x00, 0xDB, 0xE3, 0xDD, 0xE2, 0xDB, 0xAB, 0xFF};
u8 anticipation_text[] = {0xFD, 0x13, 0, 0xE7, 0xDC, 0xE9, 0xD8, 0xD8, 0xD9, 0xE6, 0xD9, 0xD8, 0x00, 0xEB, 0xDD, 0xE8, 0xDC, 0x00, 0xD5, 0xE2, 0xE8, 0xDD, 0xD7, 0xDD, 0xE4, 0xD5, 0xE8, 0xDD, 0xE3, 0xE2, 0xAB ,0xFF};
u8 dryskin_damage_text[] = {0xFD, 15, 0xB4, 0xE7, 0, 0xFD, 24, 0x0, 0xE1, 0xD5, 0xDF, 0xD9, 0xE7, 0x00, 0xDD, 0xE7, 0xFE, 0xEA, 0xE9, 0xE0, 0xE2, 0xD9, 0xE6, 0xD5, 0xD6, 0xE0, 0xD9, 0x00, 0xE8, 0xE3, 0x00, 0xE7, 0xE9, 0xE2, 0xAB, 0xFF};
u8 solarpower_text[] = {0xFD, 15, 0xB4, 0xE7, 0, 0xFD, 24, 0x0, 0xE1, 0xD5, 0xDF, 0xD9, 0xE7, 0x0, 0xDD, 0xE8, 0x0, 0xD8, 0xE6, 0xD5, 0xEB, 0x0, 0xE4, 0xE3, 0xEB, 0xD9, 0xE6, 0xFE, 0xDA, 0xE6, 0xE3, 0xE1, 0x0, 0xE8, 0xDC, 0xD9, 0x0, 0xE7, 0xE9, 0xE2, 0x0, 0xDD, 0xE2, 0x00, 0xD9, 0xEC, 0xD7, 0xDC, 0xD5, 0xE2, 0xDB, 0xD9, 0x00, 0xDA, 0xE3, 0xE6, 0x00, 0xE0, 0xDD, 0xDA, 0xD9, 0xAB, 0xFF};
u8 harvest_text[] = {0xFD, 15, 0, 0xDC, 0xD5, 0xE6, 0xEA, 0xD9, 0xE7, 0xE8, 0xD9, 0xD8, 0x00, 0xE3, 0xE2, 0xD9, 0, 0xFD, 22, 0xAB, 0xFF};
u8 healer_text[] = {0xFD, 15, 0, 0xB4, 0xE7, 0, 0xFD, 24, 0, 0xD7, 0xE9, 0xE6, 0xD9, 0xD8, 0x00, 0xDD, 0xE8, 0xE7, 0x00, 0xE4, 0xD5, 0xE6, 0xE8, 0xE2, 0xD9, 0xE6, 0xB4, 0xE7, 0xFE, 0xFD, 0x0, 0xAB, 0xFF};
u8 pickup_text[] = {0xFD, 15, 0, 0xDA, 0xE3, 0xE9, 0xE2, 0xD8, 0x00, 0xE3, 0xE2, 0xD9, 0x00, 0xFD, 22, 0xAB, 0xFF};
u8 moldbreaker_text[] = {0xFD, 0x13, 0, 0xD6, 0xE6, 0xD9, 0xD5, 0xDF, 0xE7, 0x00, 0xE8, 0xDC, 0xD9, 0x00, 0xE1, 0xE3, 0xE0, 0xD8, 0xAB, 0xFF};
u8 turboblaze_text[] = {0xFD, 0x13, 0, 0xDD, 0xE7, 0x00, 0xE6, 0xD5, 0xD8, 0xDD, 0xD5, 0xE8, 0xDD, 0xE2, 0xDB, 0x00, 0xD5, 0x00, 0xD6, 0xE0, 0xD5, 0xEE, 0xDD, 0xE2, 0xDB, 0x00, 0xD5, 0xE9, 0xE6, 0xD5, 0xAB, 0xFF};
u8 terravolt_text[] = {0xFD, 0x13, 0, 0xDD, 0xE7, 0x00, 0xE6, 0xD5, 0xD8, 0xDD, 0xD5, 0xE8, 0xDD, 0xE2, 0xDB, 0x00, 0xD5, 0x00, 0xD6, 0xE9, 0xE6, 0xE7, 0xE8, 0xDD, 0xE2, 0xDB, 0x00, 0xD5, 0xE9, 0xE6, 0xD5, 0xAB, 0xFF};
u8 downloadatk_text[] = {0xFD, 0x13, 0xB4, 0xE7, 0x0, 0xFD, 0x1A, 0, 0xE6, 0xD5, 0xDD, 0xE7, 0xD9, 0xD8, 0x00, 0xDD, 0xE8, 0xE7, 0xFE, 0xBB, 0xE8, 0xE8, 0xD5, 0xD7, 0xDF, 0xAB, 0xFF};
u8 downloadspatk_text[] = {0xFD, 0x13, 0xB4, 0xE7, 0x0, 0xFD, 0x1A, 0, 0xE6, 0xD5, 0xDD, 0xE7, 0xD9, 0xD8, 0x00, 0xDD, 0xE8, 0xE7, 0xFE, 0xCD, 0xE4, 0xAD, 0, 0xBB, 0xE8, 0xE8, 0xD5, 0xD7, 0xDF, 0xAB, 0xFF};
u8 absorbabilityboost_text[] = {0xFD, 0x10, 0xB4, 0xE7, 0, 0xFD, 0x19, 0, 0xE6, 0xD5, 0xDD, 0xE7, 0xD9, 0xD8, 0x00, 0xDD, 0xE8, 0xE7, 0xFE, 0xFD, 0x0, 0xAB ,0xFF};
u8 absorbabilityimmune_text[] = {0xFD, 0x10, 0xB4, 0xE7, 0, 0xFD, 0x19, 0, 0xE1, 0xD5, 0xDF, 0xD9, 0xE7, 0x00, 0xDD, 0xE8, 0xFE, 0xDD, 0xE1, 0xE1, 0xE9, 0xE2, 0xD9, 0x00, 0xE8, 0xE3, 0x00, 0xFD, 0x00, 0xAE, 0xE8, 0xED, 0xE4, 0xD9, 0x00, 0xE1, 0xE3, 0xEA, 0xD9, 0xE7, 0xAB, 0xFF};
u8 userteam_text[] = {Y_, o_, u_, r_, 0, t_, e_, a_, m_, Termin};
u8 foeteam_text[] = {T_, h_, e_, 0, f_, o_, e_, Apos, s_, 0, t_, e_, a_, m_, Termin};
//u8 userteam_lc_text[] = {y_, o_, u_, r_, 0, t_, e_, a_, m_, Termin};
//u8 foeteam_lc_text[] = {t_, h_, e_, 0, f_, o_, e_, Apos, s_, 0, t_, e_, a_, m_, Termin};
u8 aftermath_text[] = {0xFD, 15, 0, 0xDD, 0xE7, 0x0, 0xDC, 0xE9, 0xE6, 0xE8, 0x00, 0xD6, 0xED, 0xFE, 0xFD, 16, 0xB4, 0xE7, 0, 0xFD, 25, 0xAB, 0xFF};
u8 pickpocket_text[] = {0xFD, 16, 0, 0xE7, 0xE8, 0xE3, 0xE0, 0xD9, 0, 0xFD, 15, 0xB4, 0xE7, 0xFE, 0xFD, 22, 0xAB, 0xFF};
u8 mummy_text[] = {0xFD, 15, 0xB4, 0xE7, 0, 0xD5, 0xD6, 0xDD, 0xE0, 0xDD, 0xE8, 0xED, 0xFE, 0xD6, 0xD9, 0xD7, 0xD5, 0xE1, 0xD9, 0, 0xFD, 24, 0xAB, 0xFF};
u8 target_ability[] = {0xFD, 16, 0xB4, 0xE7, 0, 0xFD, 25, 0xAB, 0xFF};
u8 cursedbody_text[] = {0xFD, 16, 0xB4, 0xE7, 0, 0xFD, 25, 0, 0xD8, 0xDD, 0xE7, 0xD5, 0xD6, 0xE0, 0xD9, 0xD8, 0xFE, 0xFD, 15, 0xB4, 0xE7, 0, 0xFD, 0, 0xAB, 0xFF};
u8 drastically_text[] = {0xD8, 0xE6, 0xD5, 0xE7, 0xE8, 0xDD, 0xD7, 0xD5, 0xE0, 0xE0, 0xED, 0x0, 0xFF};
u8 pressure_text[] = {BuffCharac, 0x13, Space, i_, s_, Space, e_, x_, e_, r_, t_, i_, n_, g_, JumpLine, i_, t_, s_, Space, P_, r_, e_, s_, s_, u_, r_, e_, Exclam, Termin};
u8 unnerve_text[] = {0xFD, 0x0, 0, i_, s_, 0, t_, o_, o_, 0, n_, e_, r_, v_, o_, u_, s_, 0xFE, t_, o_, 0, e_, a_, t_, 0, B_, e_, r_, r_, i_, e_, s_, Exclam, Termin};
u8 aurabreak_text[] = {0xFD, 0x13, 0, r_, e_, v_, e_, r_, s_, e_, d_, 0, a_, l_, l_, 0, o_, t_, h_, e_, r_, 0xFE, P_, o_, k_, Poke_e, m_, o_, n_, Apos, s_, 0, a_, u_, r_, a_, s_, Exclam, 0xFF};
u8 fairyaura_text[] = {BuffCharac, 0x13, Space, i_, s_, Space, r_, a_, d_, i_, a_, t_, i_, n_, g_, JumpLine, a_, Space, F_, a_, i_, r_, y_, Space, A_, u_, r_, a_, Exclam, Termin};
u8 darkaura_text[] = {BuffCharac, 0x13, Space, i_, s_, Space, r_, a_, d_, i_, a_, t_, i_, n_, g_, JumpLine, a_, Space, D_, a_, r_, k_, Space, A_, u_, r_, a_, Exclam, Termin};
u8 frisk_text[] = {BuffCharac, 0x13, Space, f_, r_, i_, s_, k_, e_, d_, Space, BuffCharac, 0x10, JumpLine, a_, n_, d_, Space,
                   f_, o_, u_, n_, d_, Space, i_, t_, s_, Space, BuffCharac, 0x16, Exclam, Termin};
u8 hurtbyitem_text[] = {BuffCharac, 15, Space, i_,s_, Space, h_, u_, r_, t_, Space, b_, y_, Space, BuffCharac, 22, Exclam,0xFF};
u8 got_burned_text[] = {BuffCharac, 15, Space, g_, o_, t_, Space, b_, u_, r_, n_, e_, d_, Exclam, 0xFF};
u8 got_badlypoisoned_text[] = {BuffCharac, 15, Space, g_, o_, t_, Space, b_, a_, d_, l_, y_, 0xFE, p_, o_, i_, s_, o_, n_, e_, d_, Exclam, 0xFF};
u8 airballoon_text[] = {BuffCharac, 18, Space, i_, s_, Space, f_, l_, o_, a_, t_, i_, n_, g_, Exclam, 0xFF};
u8 bad_dreams_text[] = {BuffCharac, 0x10, Space, i_, s_, Space, t_, o_, r_, m_, e_, n_, t_, e_, d_, Space, b_, y_, JumpLine, b_, a_, d_, Space, d_, r_, e_, a_, m_, s_, Exclam, Termin};
u8 item_text[] = {BuffCharac, 16, Apos, Space, BuffCharac, 22, Exclam, 0xFF};
u8 rockyhelmet_text[] = {BuffCharac, 15, Space, i_, s_, Space, h_, u_, r_, t_, Space, b_, y_, JumpLine, BuffCharac, 16, Apos, Space, BuffCharac, 22, Exclam, 0xFF};
u8 popped_text[] = {BuffCharac, 16, Apos, Space, BuffCharac, 22, Space, p_, o_, p_, p_, e_, d_, Exclam, 0xFF};
/*0x1A6*/ u8 fellinlove_text[] = {BuffCharac, 15, Space, f_,e_,l_,l_, Space, i_, n_, Space, l_, o_, v_, e_, JumpLine, w_, i_, t_, h_, Space, BuffCharac, 16, Exclam, 0xFF};
/*0x1A7*/ u8 healblockend_text[] = {H_, e_, a_, l_, Space, B_, l_, o_, c_, k_, Space, f_, o_, r_, BuffCharac, 18, JumpLine, h_, a_, s_, Space, e_, n_, d_, e_, d_, Exclam, 0xFF};
/*0x1A8*/ u8 magicbounce_text[] = {BuffCharac, 15, Apos, s_, Space, BuffCharac, 20, JumpLine, w_, a_, s_, Space, b_, o_, u_, n_, c_, e_, d_, Space, b_, a_, c_, k_, Space, b_, y_, Space, BuffCharac, 25, Exclam, 0xFF};
/*0x1A9*/ u8 angerpoint_text[] = {0xFD, 0x10, Apos, s_, 0, 0xFD, 0x19, 0 ,m_, a_, x_, e_, d_, 0, i_, t_, s_, 0xFE, a_, t_, t_, a_, c_, k_, Exclam, 0xFF};
/*0x1AA*/ u8 stealhrock_text[] = {P_, o_, i_, n_, t_, e_, d_, Space, s_, t_, o_, n_, e_, s_, Space, d_, u_, g_, Space, i_, n_, t_, o_, JumpLine, BuffCharac, 16, Exclam, 0xFF};
/*0x1AB*/ u8 stickyweb_text[] = {BuffCharac, 16, Space, w_, a_, s_, Space, c_, a_, u_, g_, h_, t_, Space, i_, n_, Space, a_, Space, S_, t_, i_, c_, k_, y_, Space, W_, e_, b_, Exclam, 0xFF};
/*0x1AC*/ u8 gotpoisoned_text[] = {BuffCharac, 16, Space, g_, o_, t_, Space, p_, o_, i_, s_, o_, n_, e_, d_, Exclam, 0xFF};
/*0x1AD*/ u8 absorbed_spikes_text[] = {T_, o_, x_, i_, c_, Space, S_, p_, i_, k_, e_, s_, Space, h_, a_, v_, e_, Space, b_, e_, e_, n_, JumpLine, a_, b_, s_, o_, r_, b_, e_, d_, Space, b_, y_, Space, BuffCharac, 16, Exclam, 0xFF};
/*0x1AE*/ u8 lost_some_hp_text[] = {BuffCharac, 15, Space, l_, o_, s_, t_, Space, s_, o_, m_, e_, Space, o_, f_, Space, i_, t_, s_, Space, H_, P_, Exclam, 0xFF};
/*0x1AF*/ u8 tauntended_text[] = {BuffCharac, 18, Space, i_, s_, Space, n_, o_, Space, l_, o_, n_, g_, e_, r_, Space, T_, a_, u_, n_, t_, e_, d_, Exclam, 0xFF};
/*0x1B0*/ u8 tormentended_text[] = {BuffCharac, 18, Space, i_, s_, Space, n_, o_, Space, l_, o_, n_, g_, e_, r_, Space, T_, o_, r_, m_, e_, n_, e_, d_, Exclam, 0xFF};
/*0x1B1*/ u8 healblockprevents_text[] = {H_, e_, a_, l_, Space, B_, l_, o_, c_, k_, Space, p_, r_, e_, v_, e_, n_, t_, s_, JumpLine, u_, s_, a_, g_, e_, Space, o_, f_, Space, BuffCharac, 0, Exclam, 0xFF};
/*0x1B2*/ u8 gravityprevents_text[] = {G_, r_, a_, v_, i_, t_, y_, Space, p_, r_, e_, v_, e_, n_, t_, s_, JumpLine, u_, s_, a_, g_, e_, Space, o_, f_, Space, BuffCharac, 0, Exclam, 0xFF};
/*0x1B3*/ u8 embargoprevents_text[] = {C_, a_, n_, Apos, t_, Space, u_, s_, e_, Space, BuffCharac, 0, Space, u_, n_, d_, e_, r_, JumpLine, t_, h_, e_, Space, e_, f_, f_, e_, c_, t_, s_, Space, o_, f_, Space, E_, m_, b_, a_, r_, g_, o_, Exclam, 0xFF};
/*0x1B4*/ u8 aromaveilprevents_text[] = {BuffCharac, 23, Space, p_, r_, e_, v_, e_, n_, t_, s_, BuffCharac, 16, f_, r_, o_, m_, BuffCharac, 0, Exclam, 0xFF};
/*0x1B5*/ u8 spikyshield_damage[] = {BuffCharac, 16, Apos, Space, S_, p_, i_, k_, y_, Space, S_, h_, i_, e_, l_, d_, JumpLine, h_, u_, r_, t_, s_, Space, BuffCharac, 15, Exclam, 0xFF};
/*0x1B6*/ u8 symbiosispassing_text[] = {BuffCharac, 16, Space, p_, a_, s_, s_, e_, d_, Space, i_, t_, s_, JumpLine, i_, t_, e_, m_, Space, t_, o_, Space, BuffCharac, 19, Exclam, 0xFF};
/*0x1B7*/ u8 restored_hp_text[] = {BuffCharac, 16, Space, r_, e_, s_, t_, o_, r_, e_, d_, Space, i_, t_, s_, Space, H_, P_, Exclam, 0xFF};
/*0x1B8*/ u8 replacement_healed_text[] = {T_, h_, e_, Space, r_, e_, p_, l_, a_, c_, e_, m_, e_, n_, t_, Space, w_, a_, s_, Space, f_, u_, l_, l_, y_, Space, h_, e_, a_, l_, e_, d_, Exclam, 0xFF};
/*0x1B9*/ u8 telekinesis_end_text[] = {BuffCharac, 15, Space, w_, a_, s_, Space, f_, r_, e_, e_, d_, Space, f_, r_, o_, m_, JumpLine, t_, h_, e_, Space, T_, e_, l_, e_, k_, i_, n_, e_, s_, i_, s_, Exclam, 0xFF};
/*0x1BA*/ u8 embargoend_text[] = {BuffCharac, 15, Space, c_, a_, n_, Space, u_, s_, e_, JumpLine, i_, t_, e_, m_, s_, Space, a_, g_, a_, i_, n_, Exclam, 0xFF};
/*0x1BB*/ u8 magnetriseend_text[] = {BuffCharac, 15, Apos, s_, Space, e_, l_, e_, c_, t_, r_, o_, m_, a_, g_, n_, e_, t_, i_, s_, m_, JumpLine, w_, o_, r_, e_, Space, o_, f_, f_, Exclam, 0xFF};
/*0x1BC*/ u8 wrapped_text[] = {BuffCharac, 16, Space, w_, a_, s_, Space, t_, r_, a_, p_, p_, e_, d_, JumpLine, b_, y_, Space, 0xFD, 0, Exclam, 0xFF};
/*0x1BD*/ u8 nofiremoves_text[] = {T_, h_, e_, Space, F_, i_, r_, e_, Dash, t_, y_,p_,e_, a_,t_,t_,a_,c_,k_,JumpLine, f_,i_,z_,z_,l_,e_,d_,Space, o_,u_,t_,Space, i_,n_, Space,t_,h_,e_, Space, h_,e_,a_,v_,y_,Space, r_,a_,i_,n_,Exclam,0xFF};
/*0x1BE*/ u8 nowatermoves_text[] = {T_, h_, e_, Space, W_, a_, t_, e_, r_, Dash, t_, y_,p_,e_, a_,t_,t_,a_,c_,k_,JumpLine, e_,v_,a_,p_,o_,r_,a_,t_,e_,d_, Space, i_,n_, Space, t_,h_,e_, Space, h_,a_,r_,s_,h_, Space, s_,u_,n_,l_,i_,g_,h_,t_, Exclam, 0xFF};
/*0x1BF*/ u8 trickroom_ends[] = {T_, h_, e_, Space, d_, i_, m_, e_, n_, s_, i_, o_, n_, s_, Space, r_, e_, t_, u_, r_, n_, e_, d_, Space, t_, o_, Space, n_, o_, r_, m_, a_, l_, Exclam, 0xFF};
/*0x1C0*/ u8 magicroom_ends[] = {M_, a_, g_, i_, c_, Space, R_, o_, o_, m_, Space, w_, o_, r_, e_, Space, o_, f_, f_, Space, a_, n_, d_, Space, h_, e_, l_, d_, JumpLine, i_, t_, e_, m_, s_, Apos, Space, e_, f_, f_, e_, c_, t_, s_, Space, r_, e_, t_, u_, r_, n_, e_, d_, Space, t_, o_, Space, n_, o_, r_, m_, a_, l_, Exclam, 0xFF};
/*0x1C1*/ u8 wonderoom_ends[] = {W_, o_, n_, d_, e_, r_, Space, R_, o_, o_, m_, Space, w_, o_, r_, e_, Space, o_, f_, f_, Space, a_, n_, d_, Space, D_, e_, f_, e_, n_, s_, e_, Space, a_, n_, d_, JumpLine,S_, p_, Dot, Space, D_, e_, f_, Space, s_, t_, a_, t_, s_, Space, r_, e_, t_, u_, r_, n_, e_, d_, Space, t_, o_, Space, n_, o_, r_, m_, a_, l_, Exclam, 0xFF};
/*0x1C2*/ u8 gravity_ends_text[] = {G_, r_, a_, v_, i_, t_, y_, Space, r_, e_, t_, u_, r_, n_, e_, d_, Space, t_, o_, Space, n_, o_, r_, m_, a_, l_, Exclam, 0xFF};
/*0x1C3*/ u8 grassyterainends_text[] = {T_, h_, e_, Space, g_, r_, a_, s_, s_, Space, d_, i_, s_, a_, p_, p_, e_, a_, r_, e_, d_, Space, f_, r_, o_, m_, JumpLine,t_, h_, e_, Space, b_, a_, t_, t_, l_, e_, f_, i_, e_, l_, d_, Exclam, 0xFF};
/*0x1C4*/ u8 mistyterrainends_text[] = {T_, h_, e_, Space, m_, i_, s_, t_,  Space, d_, i_, s_, a_, p_, p_, e_, a_, r_, e_, d_, Space, f_, r_, o_, m_, JumpLine,t_, h_, e_, Space, b_, a_, t_, t_, l_, e_, f_, i_, e_, l_, d_, Exclam, 0xFF};
/*0x1C5*/ u8 electrerrainends_text[] = {T_, h_, e_, Space, e_, l_, e_, c_, t_, r_, i_, c_, i_, t_, y_, Space, d_, i_, s_, a_, p_, p_, e_, a_, r_, e_, d_, Space, f_, r_, o_, m_, JumpLine,t_, h_, e_, Space, b_, a_, t_, t_, l_, e_, f_, i_, e_, l_, d_, Dot, 0xFF};
/*0x1C6*/ u8 grassyterrain_heal[] = {BuffCharac, 19, Space, r_, e_, s_, t_, o_, r_, e_, d_, Space, s_, o_, m_, e_, Space, o_, f_, JumpLine, i_, t_, s_, Space, H_, P_, Space, u_, s_, i_, n_, g_, Space, G_, r_, a_, s_, s_, y_, Space, T_, e_, r_, r_, a_, i_, n_, Exclam, 0xFF};
/*0x1C7*/ u8 fogcontinues_text[] = {T_, h_, e_, Space, f_, o_, g_, Space, i_, s_, Space, d_, e_, e_, p_, Dot, Dot, Dot, 0xFF};
/*0x1C8*/ u8 fogends_text[] = {T_, h_, e_, Space, f_, o_, g_, Space, l_, i_, f_, t_, e_, d_, Exclam, 0xFF};
/*0x1C9*/ u8 obtaineditem[] = {BuffCharac, 15, Space, o_, b_, t_, a_, i_, n_, e_, d_, Space, BuffCharac, 22, Exclam, 0xFF};
/*0x1CA*/ u8 tailwind_begins_text[] = {T_, h_, e_, 0, T_, a_, i_, l_, w_, i_, n_, d_, 0, b_, l_, e_, w_, 0, f_, r_, o_, m_, 0xFE, b_, e_, h_, i_, n_, d_, 0, 0xFD, 0xF, Apos, s_, 0, t_, e_, a_, m_, Exclam, 0xFF};
/*0x1CB*/ u8 luckychant_begins_text[] = {T_, h_, e_, 0, l_, u_, c_, k_, y_, 0, c_, h_, a_, n_, t_, 0, s_, h_, i_, e_, l_, d_, e_, d_, 0, 0xFD, 0xF, Apos, s_, 0xFE, t_, e_, a_, m_, 0, f_, r_, o_, m_, 0, c_, r_, i_, t_, i_, c_, a_, l_, 0, h_, i_, t_, s_, Exclam, 0xFF};
/*0x1CC*/ u8 magnetrise_begins_text[] = {0xFD, 0xF, 0, l_, e_, v_, i_, t_, a_, t_, e_, d_, 0xFE, w_, i_, t_, h_, 0, e_, l_, e_, c_, t_, r_, o_, m_, a_, g_, n_, e_, t_, i_, s_, m_, Exclam, 0xFF};
/*0x1CD*/ u8 magicroom_start_text[] = {I_, t_, 0, c_, r_, e_, a_, t_, e_, d_, 0, a_, 0, b_, i_, z_, a_, r_, r_, e_, 0, a_, r_, e_, a_, 0, i_, n_, 0, w_, h_, i_, c_, h_, 0xFE, P_, o_, k_, Poke_e, m_, o_, n_, Apos, s_, 0, h_, e_, l_, d_, 0, i_, t_, e_, m_, s_, 0, l_, o_, s_, e_, 0, t_, h_, e_, i_, r_, 0xFB, e_, f_, f_, e_, c_, t_, s_, Exclam, 0xFF};
/*0x1CE*/ u8 trickroom_start_text[] = {0xFD, 0xF, 0, t_, w_, i_, s_, t_, e_, d_, 0xFE, t_, h_, e_, 0, d_, i_, m_, e_, n_, s_, i_, o_, n_, s_, Exclam, 0xFF};
/*0x1CD*/ u8 wonderroom_start_text[] = {I_, t_, 0, c_, r_, e_, a_, t_, e_, d_, 0, a_, 0, b_, i_, z_, a_, r_, r_, e_, 0, a_, r_, e_, a_, 0, i_, n_, 0, w_, h_, i_, c_, h_, 0xFE, D_, e_, f_, e_, n_, s_, e_, 0, a_, n_, d_, 0, S_, p_, Dot, 0, D_, e_, f_, 0, s_, t_, a_, t_, s_, 0, a_, r_, e_, 0, s_, w_, a_, p_, p_, e_, d_, Exclam, 0xFF};

void* new_strings_table[] = {&sample_text, &snowwarning_text, &extreme_sun_activation_text, &heavyrain_activation_text, &mysticalaircurrent_activation_text, &forewarn_text, &slowstart_text, &anticipation_text, &dryskin_damage_text, &solarpower_text, &harvest_text, &healer_text, &pickup_text, &moldbreaker_text, &turboblaze_text, &terravolt_text, &downloadatk_text,
&downloadspatk_text, &absorbabilityboost_text , &absorbabilityimmune_text, &userteam_text/*0x190*/, &foeteam_text/*0x191*/,
&aftermath_text, &pickpocket_text, &mummy_text, &target_ability, &cursedbody_text, &drastically_text, &pressure_text, &unnerve_text, &aurabreak_text, &fairyaura_text, &darkaura_text, &frisk_text, //0x19D
&hurtbyitem_text, &got_burned_text, &got_badlypoisoned_text, &airballoon_text, &bad_dreams_text, &item_text, &rockyhelmet_text, &popped_text, &fellinlove_text, &healblockend_text, &magicbounce_text,
&angerpoint_text, &stealhrock_text, &stickyweb_text, &gotpoisoned_text, &absorbed_spikes_text, &lost_some_hp_text, &tauntended_text, &tormentended_text,
&healblockprevents_text, &gravityprevents_text, &embargoprevents_text, &aromaveilprevents_text, &spikyshield_damage, &symbiosispassing_text,
&restored_hp_text, &replacement_healed_text, &telekinesis_end_text, &embargoend_text, &magnetriseend_text, &wrapped_text,
&nofiremoves_text, &nowatermoves_text, &trickroom_ends, &magicroom_ends, &wonderoom_ends, &gravity_ends_text, &grassyterainends_text,
&mistyterrainends_text, &electrerrainends_text, &grassyterrain_heal, &fogcontinues_text, &fogends_text, &obtaineditem,
&tailwind_begins_text, &luckychant_begins_text, &magnetrise_begins_text, &magicroom_start_text, &trickroom_start_text, &wonderroom_start_text};

void battle_string_loader(u16 string_id)
{
    string_id -= 0x17C;
    display_string_in_battle(new_strings_table[string_id]);
    return;
}

extern void call_ability_effects();

void apply_burn_animation()
{
    u8 active = active_bank;
    active_bank = bank_attacker;
    new_battlestruct.ptr->various.var1 = 0x10;
    new_battlestruct.ptr->various.var2 = 0;
    prepare_status_animation(0, 0, new_battlestruct.ptr->various.var1);
    mark_buffer_bank_for_execution(bank_attacker);
    active_bank = active;
    return;
}

void change_attacker_item()
{
    active_bank = bank_attacker;
    prepare_setattributes_in_battle(0, 2, 0, 4, &battle_participants[bank_attacker].held_item);
    mark_buffer_bank_for_execution(bank_attacker);
}

void try_to_raise_spd()
{
    if (battle_participants[new_battlestruct.ptr->various.active_bank].spd_buff != 0xC)
    {
        battle_scripting.stat_changer = 0x13;
        battlescript_push();
        battlescripts_curr_instruction = &changetargetstat_bs;
    }
    return;
}

void try_to_lower_def()
{
    if (battle_participants[new_battlestruct.ptr->various.active_bank].def_buff > 0)
    {
        battle_scripting.stat_changer = 0x92;
        battlescript_push();
        battlescripts_curr_instruction = &changetargetstat_bs;
    }
    return;
}

void changestatvar1()
{
    if (new_battlestruct.ptr->various.var1)
    {
        battle_scripting.stat_changer = new_battlestruct.ptr->various.var1;
        battlescript_push();
        battlescripts_curr_instruction = &changetargetstat_bs;
    }
    return;
}

void changestatvar2()
{
    if (new_battlestruct.ptr->various.var2)
    {
        battle_scripting.stat_changer = new_battlestruct.ptr->various.var2;
        battlescript_push();
        battlescripts_curr_instruction = &changetargetstat_bs;
    }
    return;
}

void frisk_target_item()
{   u16 curr_item=battle_participants[bank_target].held_item;
    if (curr_item)
    {
        last_used_item=curr_item;
        b_std_message(0x19D,battle_scripting.active_bank);
        record_usage_of_item(bank_target, get_item_effect(bank_target, 0));
        battle_communication_struct.is_message_displayed=1;
    }
    else
        battle_communication_struct.is_message_displayed=0;

    return;
}

void set_stat_msg_buffer()
{
    u8 stat=battle_scripting.stat_changer&0xF;
    battle_text_buff1[0] = 0xFD;
    battle_text_buff1[1] = 5;
    battle_text_buff1[2] = stat;
    battle_text_buff1[3] = 0xFF;
}

void set_type_msg_buffer()
{
    u8 move_type=battle_stuff_ptr.ptr->dynamic_move_type&0x3F;
    if (!move_type)
        move_type = move_table[current_move].type;
    battle_text_buff1[0] = 0xFD;
    battle_text_buff1[1] = 3;
    battle_text_buff1[2] = move_type;
    battle_text_buff1[3] = 0xFF;
}

void set_team_msg_buffer()
{
    battle_text_buff1[0] = 0xFD;
    battle_text_buff1[1] = 0;
    if (is_bank_from_opponent_side(battle_scripting.active_bank))
        battle_text_buff1[2] = 0x90;
    else
        battle_text_buff1[2] = 0x91;
    battle_text_buff1[3] = 0x1;
    battle_text_buff1[4] = 0xFF;
}

u32 get_1_8_of_max_hp(u8 bank);

void bad_dreams_damage_calc()
{
    damage_loc=get_1_8_of_max_hp(bank_target);
}

void weaknesspolicy()
{
    if (battle_participants[battle_scripting.active_bank].sp_atk_buff != 0xC)
    {
        battlescript_push();
        battlescripts_curr_instruction = &weaknesspolicyspattack;
    }
    if (battle_participants[battle_scripting.active_bank].atk_buff != 0xC)
    {
        battlescript_push();
        battlescripts_curr_instruction = &weaknesspolicyattack;
    }
    return;
}

void mentalherb()
{
    u8 bank = battle_scripting.active_bank;
    if (disable_structs[bank].disable_timer)
    {
        disable_structs[bank].disable_timer = 0;
        disable_structs[bank].disabled_move = 0;
        battlescript_push();
        battlescripts_curr_instruction = &disable_end_bs;
    }
    if (disable_structs[bank].encore_timer)
    {
        disable_structs[bank].encore_timer = 0;
        disable_structs[bank].encored_move = 0;
        battlescript_push();
        battlescripts_curr_instruction = &encore_end_bs;
    }
    if (disable_structs[bank].taunt_timer)
    {
        disable_structs[bank].taunt_timer = 0;
        battlescript_push();
        battlescripts_curr_instruction = &taunt_end_bs;
    }
    if (new_battlestruct.ptr->bank_affecting[bank].heal_block)
    {
        new_battlestruct.ptr->bank_affecting[bank].heal_block = 0;
        battlescript_push();
        battlescripts_curr_instruction = &healblock_end_bs;
    }
    return;
}

void placeholder0x14()
{
    return;
}

void hazards_bank_switcher()
{
    new_battlestruct.ptr->various.active_bank = bank_target;
    bank_target = new_battlestruct.ptr->various.var1;
    return;
}

void hazards_bank_return()
{
    bank_target = new_battlestruct.ptr->various.active_bank;
    return;
}

u32 percent_boost(u32 number, u16 percent);

void leechseed_update()
{
    if (new_battlestruct.ptr->bank_affecting[bank_target].heal_block)
        damage_loc = 0;
    else if (get_item_effect(bank_target, 1) == ITEM_EFFECT_BIGROOT)
        damage_loc = percent_boost(damage_loc, 30);
}

void callasm_stat_change(u8 bank, void* battlescript_ptr)
{
    battle_scripting.stat_changer = read_byte(battlescripts_curr_instruction);
    battlescripts_curr_instruction++;
    battlescript_push();
    battlescripts_curr_instruction = battlescript_ptr;
    return;
}

void target_stat_change()
{
    callasm_stat_change(bank_target, &changetargetstat_bs);
    return;
}

void attacker_stat_change()
{
    callasm_stat_change(bank_attacker, &changeattackerstat_bs);
    return;
}

void moxie_stat_raise()
{
    if ((current_move == MOVE_BLOCK || check_ability(bank_attacker, ABILITY_MOXIE)) && bank_attacker != bank_target && DAMAGING_MOVE)
    {
        //check if that's the last opponent pokemon, if yes, then we'll skip the animation
        if (is_bank_from_opponent_side(bank_target))
        {
            for (u8 i = 0; i < 6; i++)
            {
                if (!(get_attributes(&party_opponent[i], ATTR_CURRENT_HP, 0) == 0 || get_attributes(&party_opponent[i], ATTR_IS_EGG, 0) || get_attributes(&party_opponent[i], ATTR_SPECIES, 0) == 0))
                    break;
                if (i == 5)
                    return;
            }
        }
        battlescript_push();
        battlescripts_curr_instruction = &changeattackerstat_bs;
        battle_scripting.stat_changer = 0x21;
    }
    return;
}

void grassyterrainn_heal()
{
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        if (!new_battlestruct.ptr->bank_affecting[i].grassyterrain_heal && get_airborne_state(i, 0, 1) <= 2 && battle_participants[i].current_hp < battle_participants[i].max_hp)
        {
            new_battlestruct.ptr->bank_affecting[i].grassyterrain_heal = 1;
            battlescripts_curr_instruction -= 3;
            battlescript_push();
            battlescripts_curr_instruction = &grassyheal;
            battle_scripting.active_bank = i;
            damage_loc = get_1_16_of_max_hp(i) * -1;
            break;
        }
        if (i == no_of_all_banks)
            break;
    }
    return;
}

void callitemeffects()
{
    item_battle_effects(1, active_bank, 0);
    return;
}

void* callasm_table[] = {&call_ability_effects, &apply_burn_animation, &change_attacker_item, &try_to_lower_def, &try_to_raise_spd,
&changestatvar1, &changestatvar2, &frisk_target_item, &set_stat_msg_buffer, &set_type_msg_buffer, &set_team_msg_buffer, &bad_dreams_damage_calc,
&weaknesspolicy, &mentalherb, &placeholder0x14, &hazards_bank_switcher, &hazards_bank_return, &leechseed_update,
&target_stat_change, &attacker_stat_change, &moxie_stat_raise, &grassyterrainn_heal, &callitemeffects};

void callasm_cmd()
{
    void (*command) (void);
    u8 command_id_ls = read_byte(battlescripts_curr_instruction + 1);
    u8 command_id_ms = read_byte(battlescripts_curr_instruction + 2);
    battlescripts_curr_instruction += 3;
    command = callasm_table[(command_id_ms<<8)+command_id_ls];
    command();
}
