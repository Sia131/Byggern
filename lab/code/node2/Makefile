# List all source files to be compiled; separate with space
SOURCE_FILES := main.c UART.c SPI.c MCP.c CAN.c input_com.c pwm.c ADC_internal.c timer.c goal.c TWI_Master.c DAC.c motor.c controller.c solenoid.c node2.c

# Set this flag to "yes" (no quotes) to use JTAG; otherwise ISP (SPI) is used
PROGRAM_WITH_JTAG := yes
PROGRAM_162 := ye

# Feel free to ignore anything below this line
PROGRAMMER := atmelice_isp
ifeq ($(PROGRAM_WITH_JTAG), yes)
	PROGRAMMER := atmelice
endif

BUILD_DIR := build

TARGET_CPU := atmega2560
TARGET_DEVICE := m2560
ifeq ($(PROGRAM_162), yes)
	TARGET_CPU := atmega162
	TARGET_DEVICE := m162	
	SOURCE_FILES := main.c UART.c SPI.c MCP.c CAN.c input_com.c user_input.c OLED.c OLED_SRAM.c memory_map.c menu.c timer.c ADC.c node1.c
endif

CC := avr-gcc
CFLAGS := -O -std=c11 -mmcu=$(TARGET_CPU) -Werror -Ilib/inc -Inode1/inc -Inode2/inc
VPATH = lib:node1:node2

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

.DEFAULT_GOAL := $(BUILD_DIR)/main.hex

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.hex: $(OBJECT_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/a.out
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/a.out $(BUILD_DIR)/main.hex

.PHONY: flash
flash: $(BUILD_DIR)/main.hex
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U flash:w:$(BUILD_DIR)/main.hex:i

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: erase
erase:
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -e