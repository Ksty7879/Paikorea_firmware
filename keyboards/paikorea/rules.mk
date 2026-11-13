POINTING_DEVICE_DRIVER = azoteq_iqs5xx

# Build a side-specific image: make paikorea:vial PAIKOREA_SIDE=left|right
# The image forces the EEPROM handedness to that side on every boot.
ifeq ($(strip $(PAIKOREA_SIDE)), left)
    OPT_DEFS += -DINIT_EE_HANDS_LEFT
endif
ifeq ($(strip $(PAIKOREA_SIDE)), right)
    OPT_DEFS += -DINIT_EE_HANDS_RIGHT
endif
