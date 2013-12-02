#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,---------------.
     * |Esc|Tab|=  |Bs |
     * |---+---+---+---|
     * |Num|/  |*  |-  |
     * |---+---+---+---|
     * |7  |8  |9  |+  |
     * |---+---+---|   |
     * |4  |5  |6  |   |
     * |---+---+---+---|
     * |1  |2  |3  |Ent|
     * |---+---+---|   |
     * |0      |.  |   |
     * `---------------'
     */
    [0] = KEYMAP(
        ESC, TAB, PEQL,BSPC, \
        NLCK,PSLS,PAST,PMNS, \
        P7,  P8,  P9,  PPLS, \
        P4,  P5,  P6,  PENT, \
        P1,  P2,  P3,  PENT, \
        P0,  NO,  PDOT,NO)
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
static const uint16_t fn_actions[] PROGMEM = {
#endif
};
