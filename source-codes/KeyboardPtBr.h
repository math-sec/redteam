/**
 * KeyboardPtBr.h — Teclado ABNT2 (PT-BR) para ATmega32U4
 * Feito por Matheus Lambert (https://www.linkedin.com/in/matheus-lambert-sec/) e (https://github.com/math-sec/redteam/edit/main/source-codes/KeyboardPtBr.h)
 *
 * Biblioteca para placas com ATmega32U4 (Pro Micro, Arduino Micro, Leonardo)
 * que envia teclas pelo USB HID nativo usando layout ABNT2.
 *
 * Baseada na DigiKeyboardPtBr.h de Eduardo Gadotti (https://github.com/Gadotti)
 * Refatorada para substituir DigiKeyboard.h (V-USB / Digispark) por Keyboard.h (HID nativo).
 *
 * Uso:
 *   #include "KeyboardPtBr.h"
 *
 *   void setup() {
 *       KeyboardPtBr.begin();
 *       delay(1000);
 *       KeyboardPtBr.print("Olá, mundo! Ação ção");
 *       KeyboardPtBr.sendKeyStroke(KEY_R_PTBR, PTBR_MOD_GUI_LEFT); // Win+R
 *   }
 */

#ifndef KEYBOARD_PTBR_H
#define KEYBOARD_PTBR_H

#include <Arduino.h>
#include <HID.h>
#include <Keyboard.h>

// ─── Modificadores USB HID (para uso direto com sendKeyStroke) ───────────────
#define PTBR_MOD_NONE           0x00
#define PTBR_MOD_CTRL_LEFT      0x01
#define PTBR_MOD_SHIFT_LEFT     0x02
#define PTBR_MOD_ALT_LEFT       0x04
#define PTBR_MOD_GUI_LEFT       0x08
#define PTBR_MOD_CTRL_RIGHT     0x10
#define PTBR_MOD_SHIFT_RIGHT    0x20
#define PTBR_MOD_ALT_RIGHT      0x40   // AltGr
#define PTBR_MOD_GUI_RIGHT      0x80

// ─── Aliases de compatibilidade com DigiKeyboard ────────────────────────────
//  Permite usar os nomes antigos MOD_GUI_LEFT, MOD_SHIFT_LEFT, etc.
#ifndef MOD_CONTROL_LEFT
  #define MOD_CONTROL_LEFT   PTBR_MOD_CTRL_LEFT
#endif
#ifndef MOD_SHIFT_LEFT
  #define MOD_SHIFT_LEFT     PTBR_MOD_SHIFT_LEFT
#endif
#ifndef MOD_ALT_LEFT
  #define MOD_ALT_LEFT       PTBR_MOD_ALT_LEFT
#endif
#ifndef MOD_GUI_LEFT
  #define MOD_GUI_LEFT       PTBR_MOD_GUI_LEFT
#endif
#ifndef MOD_CONTROL_RIGHT
  #define MOD_CONTROL_RIGHT  PTBR_MOD_CTRL_RIGHT
#endif
#ifndef MOD_SHIFT_RIGHT
  #define MOD_SHIFT_RIGHT    PTBR_MOD_SHIFT_RIGHT
#endif
#ifndef MOD_ALT_RIGHT
  #define MOD_ALT_RIGHT      PTBR_MOD_ALT_RIGHT
#endif
#ifndef MOD_GUI_RIGHT
  #define MOD_GUI_RIGHT      PTBR_MOD_GUI_RIGHT
#endif

// ─── Scancodes de teclas úteis (para uso com sendKeyStroke) ──────────────────
#define KEY_A_PTBR    0x04
#define KEY_B_PTBR    0x05
#define KEY_C_PTBR    0x06
#define KEY_D_PTBR    0x07
#define KEY_E_PTBR    0x08
#define KEY_F_PTBR    0x09
#define KEY_G_PTBR    0x0A
#define KEY_H_PTBR    0x0B
#define KEY_I_PTBR    0x0C
#define KEY_J_PTBR    0x0D
#define KEY_K_PTBR    0x0E
#define KEY_L_PTBR    0x0F
#define KEY_M_PTBR    0x10
#define KEY_N_PTBR    0x11
#define KEY_O_PTBR    0x12
#define KEY_P_PTBR    0x13
#define KEY_Q_PTBR    0x14
#define KEY_R_PTBR    0x15
#define KEY_S_PTBR    0x16
#define KEY_T_PTBR    0x17
#define KEY_U_PTBR    0x18
#define KEY_V_PTBR    0x19
#define KEY_W_PTBR    0x1A
#define KEY_X_PTBR    0x1B
#define KEY_Y_PTBR    0x1C
#define KEY_Z_PTBR    0x1D

#define KEY_1_PTBR    0x1E
#define KEY_2_PTBR    0x1F
#define KEY_3_PTBR    0x20
#define KEY_4_PTBR    0x21
#define KEY_5_PTBR    0x22
#define KEY_6_PTBR    0x23
#define KEY_7_PTBR    0x24
#define KEY_8_PTBR    0x25
#define KEY_9_PTBR    0x26
#define KEY_0_PTBR    0x27

#define KEY_ENTER_PTBR      0x28
#define KEY_ESCAPE_PTBR     0x29
#define KEY_BACKSPACE_PTBR  0x2A
#define KEY_TAB_PTBR        0x2B
#define KEY_SPACE_PTBR      0x2C
#define KEY_CEDILLA_PTBR    0x33   // ç

#define KEY_F1_PTBR   0x3A
#define KEY_F2_PTBR   0x3B
#define KEY_F3_PTBR   0x3C
#define KEY_F4_PTBR   0x3D
#define KEY_F5_PTBR   0x3E
#define KEY_F6_PTBR   0x3F
#define KEY_F7_PTBR   0x40
#define KEY_F8_PTBR   0x41
#define KEY_F9_PTBR   0x42
#define KEY_F10_PTBR  0x43
#define KEY_F11_PTBR  0x44
#define KEY_F12_PTBR  0x45

#define KEY_DELETE_PTBR     0x4C
#define KEY_INSERT_PTBR     0x49
#define KEY_HOME_PTBR       0x4A
#define KEY_END_PTBR        0x4D
#define KEY_PAGEUP_PTBR     0x4B
#define KEY_PAGEDOWN_PTBR   0x4E

#define KEY_RIGHT_PTBR  0x4F
#define KEY_LEFT_PTBR   0x50
#define KEY_DOWN_PTBR   0x51
#define KEY_UP_PTBR     0x52

#define KEY_CAPSLOCK_PTBR   0x39
#define KEY_PRINTSCREEN_PTBR 0x46
#define KEY_SCROLLLOCK_PTBR  0x47
#define KEY_NUMLOCK_PTBR     0x53

// ─── Flags internas para o mapa (high byte = modificador USB HID) ────────────
#define _MAP_CTRL_L    (1<<8)
#define _MAP_SHIFT_L   (1<<9)
#define _MAP_ALT_L     (1<<10)
#define _MAP_GUI_L     (1<<11)
#define _MAP_CTRL_R    (1<<12)
#define _MAP_SHIFT_R   (1<<13)
#define _MAP_ALT_R     (1<<14)   // AltGr
#define _MAP_GUI_R     (1<<15)

// ─── Dead keys no layout ABNT2 ──────────────────────────────────────────────
//  Tecla à direita do P (scancode 0x2F):  ´ (sem mod) / ` (com Shift)
//  Tecla à direita do Ç (scancode 0x34):  ~ (sem mod) / ^ (com Shift)
#define _DEAD_ACUTE     0x2F
#define _DEAD_TILDE     0x34

// ─── Mapa ASCII 0‑127 → scancode ABNT2 + modificadores ─────────────────────
// Cada entrada: low byte = scancode USB HID, high byte = modificador USB HID.
// Mapeamento original de Eduardo Gadotti, mantido intacto.
static const uint16_t _asciiMapPtBr[128] PROGMEM = {
    0x00,                          //  0  NUL
    0x00,                          //  1  SOH
    0x00,                          //  2  STX
    0x00,                          //  3  ETX
    0x00,                          //  4  EOT
    0x00,                          //  5  ENQ
    0x00,                          //  6  ACK
    0x00,                          //  7  BEL
    0x2A,                          //  8  BS  Backspace
    0x2B,                          //  9  TAB Tab
    0x28,                          // 10  LF  Enter
    0x00,                          // 11  VT
    0x00,                          // 12  FF
    0x00,                          // 13  CR
    0x00,                          // 14  SO
    0x00,                          // 15  SI
    0x00,                          // 16  DEL
    0x00,                          // 17  DC1
    0x00,                          // 18  DC2
    0x00,                          // 19  DC3
    0x00,                          // 20  DC4
    0x00,                          // 21  NAK
    0x00,                          // 22  SYN
    0x00,                          // 23  ETB
    0x00,                          // 24  CAN
    0x00,                          // 25  EM
    0x00,                          // 26  SUB
    0x00,                          // 27  ESC
    0x00,                          // 28  FS
    0x00,                          // 29  GS
    0x00,                          // 30  RS
    0x00,                          // 31  US

    0x2C,                          // 32  ' ' (espaço)
    0x1E | _MAP_SHIFT_L,           // 33  !
    0x35 | _MAP_SHIFT_L,           // 34  "
    0x20 | _MAP_SHIFT_L,           // 35  #
    0x21 | _MAP_SHIFT_L,           // 36  $
    0x22 | _MAP_SHIFT_L,           // 37  %
    0x24 | _MAP_SHIFT_L,           // 38  &
    0x35,                          // 39  '
    0x26 | _MAP_SHIFT_L,           // 40  (
    0x27 | _MAP_SHIFT_L,           // 41  )
    0x25 | _MAP_SHIFT_L,           // 42  *
    0x2E | _MAP_SHIFT_L,           // 43  +
    0x36,                          // 44  ,
    0x2D,                          // 45  -
    0x37,                          // 46  .
    0x14 | _MAP_ALT_R,             // 47  /   (AltGr+Q no ABNT2/Windows)
    0x27,                          // 48  0
    0x1E,                          // 49  1
    0x1F,                          // 50  2
    0x20,                          // 51  3
    0x21,                          // 52  4
    0x22,                          // 53  5
    0x23,                          // 54  6
    0x24,                          // 55  7
    0x25,                          // 56  8
    0x26,                          // 57  9
    0x38 | _MAP_SHIFT_L,           // 58  :
    0x38,                          // 59  ;
    0x36 | _MAP_SHIFT_L,           // 60  <
    0x2E,                          // 61  =
    0x37 | _MAP_SHIFT_L,           // 62  >
    0x1A | _MAP_ALT_R,             // 63  ?   (AltGr+W no ABNT2/Windows)
    0x1F | _MAP_SHIFT_L,           // 64  @

    // Maiúsculas A‑Z (Shift + scancode da letra)
    0x04 | _MAP_SHIFT_L,           // 65  A
    0x05 | _MAP_SHIFT_L,           // 66  B
    0x06 | _MAP_SHIFT_L,           // 67  C
    0x07 | _MAP_SHIFT_L,           // 68  D
    0x08 | _MAP_SHIFT_L,           // 69  E
    0x09 | _MAP_SHIFT_L,           // 70  F
    0x0A | _MAP_SHIFT_L,           // 71  G
    0x0B | _MAP_SHIFT_L,           // 72  H
    0x0C | _MAP_SHIFT_L,           // 73  I
    0x0D | _MAP_SHIFT_L,           // 74  J
    0x0E | _MAP_SHIFT_L,           // 75  K
    0x0F | _MAP_SHIFT_L,           // 76  L
    0x10 | _MAP_SHIFT_L,           // 77  M
    0x11 | _MAP_SHIFT_L,           // 78  N
    0x12 | _MAP_SHIFT_L,           // 79  O
    0x13 | _MAP_SHIFT_L,           // 80  P
    0x14 | _MAP_SHIFT_L,           // 81  Q
    0x15 | _MAP_SHIFT_L,           // 82  R
    0x16 | _MAP_SHIFT_L,           // 83  S
    0x17 | _MAP_SHIFT_L,           // 84  T
    0x18 | _MAP_SHIFT_L,           // 85  U
    0x19 | _MAP_SHIFT_L,           // 86  V
    0x1A | _MAP_SHIFT_L,           // 87  W
    0x1B | _MAP_SHIFT_L,           // 88  X
    0x1C | _MAP_SHIFT_L,           // 89  Y
    0x1D | _MAP_SHIFT_L,           // 90  Z

    0x30,                          // 91  [
    0x64,                          // 92  backslash
    0x32,                          // 93  ]
    0x35,                          // 94  ^
    0x2D | _MAP_SHIFT_L,           // 95  _
    0x2E | _MAP_SHIFT_L,           // 96  `

    // Minúsculas a‑z
    0x04,                          // 97   a
    0x05,                          // 98   b
    0x06,                          // 99   c
    0x07,                          // 100  d
    0x08,                          // 101  e
    0x09,                          // 102  f
    0x0A,                          // 103  g
    0x0B,                          // 104  h
    0x0C,                          // 105  i
    0x0D,                          // 106  j
    0x0E,                          // 107  k
    0x0F,                          // 108  l
    0x10,                          // 109  m
    0x11,                          // 110  n
    0x12,                          // 111  o
    0x13,                          // 112  p
    0x14,                          // 113  q
    0x15,                          // 114  r
    0x16,                          // 115  s
    0x17,                          // 116  t
    0x18,                          // 117  u
    0x19,                          // 118  v
    0x1A,                          // 119  w
    0x1B,                          // 120  x
    0x1C,                          // 121  y
    0x1D,                          // 122  z

    0x30 | _MAP_SHIFT_L,           // 123  {
    0x64 | _MAP_SHIFT_L,           // 124  |
    0x32 | _MAP_SHIFT_L,           // 125  }
    0x64,                          // 126  ~
    0x00                           // 127  DEL
};


// ═════════════════════════════════════════════════════════════════════════════
class KeyboardPtBr_ {
public:

    // ── Inicialização / Finalização ─────────────────────────────────────────
    void begin() {
        Keyboard.begin();
    }

    void end() {
        Keyboard.end();
    }

    // ── sendKeyStroke ───────────────────────────────────────────────────────
    //  Envia um scancode USB HID com modificadores opcionais (press + release).
    //  Equivalente a DigiKeyboard.sendKeyStroke().
    //
    //  Exemplos:
    //    KeyboardPtBr.sendKeyStroke(KEY_R_PTBR, PTBR_MOD_GUI_LEFT);  // Win+R
    //    KeyboardPtBr.sendKeyStroke(KEY_ENTER_PTBR);                  // Enter
    //    KeyboardPtBr.sendKeyStroke(KEY_C_PTBR, PTBR_MOD_CTRL_LEFT); // Ctrl+C
    //
    void sendKeyStroke(uint8_t keycode, uint8_t modifiers = 0) {
        _sendRawReport(modifiers, keycode);
        delay(15);
        _releaseAllKeys();
        delay(15);
    }

    // ── write ───────────────────────────────────────────────────────────────
    //  Envia um único byte (ASCII ou parte de sequência UTF‑8).
    //  Retorna 1 se o byte foi processado.
    //
    size_t write(uint8_t chr) {

        // ── Continuação de sequência UTF‑8 de 2 bytes ───────────────────
        if (_utf8First != 0) {
            uint8_t first = _utf8First;
            _utf8First = 0;
            if (first == 0xC3) {
                _handleLatin1Accented(chr);
            }
            // Outras faixas UTF‑8 podem ser adicionadas aqui.
            return 1;
        }

        // ── Início de sequência UTF‑8 de 2 bytes (0xC0–0xDF) ───────────
        if (chr >= 0xC0 && chr <= 0xDF) {
            _utf8First = chr;
            return 1;
        }

        // ── Byte > 127 fora de sequência UTF‑8 conhecida → ignorar ─────
        if (chr >= 128) {
            return 0;
        }

        // ── ASCII puro (0–127) → consultar o mapa ──────────────────────
        uint16_t mapped = pgm_read_word_near(_asciiMapPtBr + chr);
        uint8_t keycode   = mapped & 0xFF;
        uint8_t modifiers = (mapped >> 8) & 0xFF;

        if (keycode == 0 && modifiers == 0 && chr != 0) {
            return 0;   // Caractere sem mapeamento
        }

        sendKeyStroke(keycode, modifiers);
        return 1;
    }

    // ── print / println ─────────────────────────────────────────────────────
    void print(const char* str) {
        if (!str) return;
        while (*str) {
            write((uint8_t)*str);
            str++;
        }
    }

    void println(const char* str = "") {
        print(str);
        write('\n');    // '\n' → Enter (scancode 0x28 via mapa)
    }

    void print(const String& s) {
        for (unsigned int i = 0; i < s.length(); i++) {
            write((uint8_t)s[i]);
        }
    }

    void println(const String& s) {
        print(s);
        write('\n');
    }

    // Sobrecarga para char único
    void print(char c) { write((uint8_t)c); }

    // ── pressKey / releaseKey ───────────────────────────────────────────────
    //  Para manter uma tecla pressionada (útil para combos mais complexos).
    //
    void pressKey(uint8_t keycode, uint8_t modifiers = 0) {
        _sendRawReport(modifiers, keycode);
    }

    void releaseAll() {
        _releaseAllKeys();
    }

    // ── delay (compatibilidade com DigiKeyboard.delay) ──────────────────────
    //  No Digispark, delay() precisava manter o V-USB ativo.
    //  No ATmega32U4 o USB é nativo, então é só um wrapper para delay().
    //
    void delay(unsigned long ms) {
        ::delay(ms);
    }

    // ── update (compatibilidade com DigiKeyboard.update) ────────────────────
    //  No Digispark era necessário chamar periodicamente para manter o V-USB.
    //  No ATmega32U4 é no-op — USB é gerenciado pelo hardware.
    //
    void update() { /* no-op */ }


private:
    uint8_t _utf8First = 0;

    // ── Enviar HID report cru ───────────────────────────────────────────────
    void _sendRawReport(uint8_t modifiers, uint8_t keycode) {
        uint8_t report[8] = {0};
        report[0] = modifiers;
        // report[1] = 0x00;  // reservado
        report[2] = keycode;
        HID().SendReport(2, report, sizeof(report));
    }

    void _releaseAllKeys() {
        uint8_t report[8] = {0};
        HID().SendReport(2, report, sizeof(report));
    }

    // ── Tratar caracteres acentuados Latin‑1 (UTF‑8: 0xC3 + segundo byte) ──
    //
    //  No ABNT2, caracteres acentuados são compostos por dead key + letra.
    //  Dead keys usadas:
    //    ´ (agudo)   → scancode 0x2F, sem modificador
    //    ` (grave)   → scancode 0x2F, com Shift
    //    ~ (til)     → scancode 0x34, sem modificador
    //    ^ (circunf) → scancode 0x34, com Shift
    //
    //  ç e Ç possuem tecla própria (scancode 0x33).
    //
    void _handleLatin1Accented(uint8_t second) {

        uint8_t deadKey = 0;
        uint8_t deadMod = 0;
        uint8_t baseKey = 0;
        uint8_t baseMod = 0;

        switch (second) {

            // ── ç / Ç — tecla dedicada no ABNT2 ────────────────────────
            case 0xA7: sendKeyStroke(0x33);                         return; // ç
            case 0x87: sendKeyStroke(0x33, PTBR_MOD_SHIFT_LEFT);    return; // Ç

            // ── Acento agudo (´) ────────────────────────────────────────
            case 0xA1: deadKey = _DEAD_ACUTE; baseKey = 0x04; break;  // á
            case 0xA9: deadKey = _DEAD_ACUTE; baseKey = 0x08; break;  // é
            case 0xAD: deadKey = _DEAD_ACUTE; baseKey = 0x0C; break;  // í
            case 0xB3: deadKey = _DEAD_ACUTE; baseKey = 0x12; break;  // ó
            case 0xBA: deadKey = _DEAD_ACUTE; baseKey = 0x18; break;  // ú
            // maiúsculas
            case 0x81: deadKey = _DEAD_ACUTE; baseKey = 0x04; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Á
            case 0x89: deadKey = _DEAD_ACUTE; baseKey = 0x08; baseMod = PTBR_MOD_SHIFT_LEFT; break; // É
            case 0x8D: deadKey = _DEAD_ACUTE; baseKey = 0x0C; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Í
            case 0x93: deadKey = _DEAD_ACUTE; baseKey = 0x12; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Ó
            case 0x9A: deadKey = _DEAD_ACUTE; baseKey = 0x18; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Ú

            // ── Acento grave (`) — dead key: Shift + 0x2F ──────────────
            case 0xA0: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x04; break; // à
            case 0xA8: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x08; break; // è
            case 0xAC: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x0C; break; // ì
            case 0xB2: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x12; break; // ò
            case 0xB9: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x18; break; // ù
            // maiúsculas
            case 0x80: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x04; baseMod = PTBR_MOD_SHIFT_LEFT; break; // À
            case 0x88: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x08; baseMod = PTBR_MOD_SHIFT_LEFT; break; // È
            case 0x8C: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x0C; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Ì
            case 0x92: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x12; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Ò
            case 0x99: deadKey = _DEAD_ACUTE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x18; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Ù

            // ── Til (~) — dead key: 0x34 sem modificador ───────────────
            case 0xA3: deadKey = _DEAD_TILDE; baseKey = 0x04; break;  // ã
            case 0xB5: deadKey = _DEAD_TILDE; baseKey = 0x12; break;  // õ
            case 0xB1: deadKey = _DEAD_TILDE; baseKey = 0x11; break;  // ñ
            // maiúsculas
            case 0x83: deadKey = _DEAD_TILDE; baseKey = 0x04; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Ã
            case 0x95: deadKey = _DEAD_TILDE; baseKey = 0x12; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Õ
            case 0x91: deadKey = _DEAD_TILDE; baseKey = 0x11; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Ñ

            // ── Circunflexo (^) — dead key: Shift + 0x34 ──────────────
            case 0xA2: deadKey = _DEAD_TILDE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x04; break; // â
            case 0xAA: deadKey = _DEAD_TILDE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x08; break; // ê
            case 0xB4: deadKey = _DEAD_TILDE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x12; break; // ô
            // maiúsculas
            case 0x82: deadKey = _DEAD_TILDE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x04; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Â
            case 0x8A: deadKey = _DEAD_TILDE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x08; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Ê
            case 0x94: deadKey = _DEAD_TILDE; deadMod = PTBR_MOD_SHIFT_LEFT; baseKey = 0x12; baseMod = PTBR_MOD_SHIFT_LEFT; break; // Ô

            default:
                return;   // Caractere acentuado não mapeado
        }

        // Compor: dead key → release → letra
        sendKeyStroke(deadKey, deadMod);
        delay(20);
        sendKeyStroke(baseKey, baseMod);
    }
};

// ── Instância global ────────────────────────────────────────────────────────
KeyboardPtBr_ KeyboardPtBr;

// ── Alias de compatibilidade com DigiKeyboardPtBr ───────────────────────────
//  Permite usar o nome antigo sem alterar sketches existentes.
#define DigiKeyboardPtBr KeyboardPtBr

#endif // KEYBOARD_PTBR_H
