TARGET_EXEC ?= example.elf
TARGET_HEX := example.hex

PREFIX := riscv-none-embed-
AS := $(PREFIX)gcc
CC := $(PREFIX)gcc
CXX := $(PREFIX)g++
CP := $(PREFIX)objcopy
HEX := $(CP) -O ihex -S

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
VENDOR_DIR ?= ./vendor
ALL_SRC_DIRS := $(SRC_DIRS) $(VENDOR_DIR)/Core $(VENDOR_DIR)/Debug $(VENDOR_DIR)/Peripheral $(VENDOR_DIR)/Startup $(VENDOR_DIR)/User

FLASH_PROG ?= wlink 

SRCS := $(shell find $(ALL_SRC_DIRS) -name *.cpp -or -name *.c -or -name *.S)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(ALL_SRC_DIRS) -type f -name \*.h | sed 's!/[^/]*$$!!' | sort -u)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) $(EXTRA_INC)

FLAGS ?= -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g
DEFINES ?= -DSYSCLK_FREQ_144MHz
ASFLAGS ?= $(FLAGS) -x assembler $(INC_FLAGS) $(DEFINES) -MMD -MP
CPPFLAGS ?=  $(FLAGS) $(INC_FLAGS) $(DEFINES) -std=gnu99 -MMD -MP
LDFLAGS ?= $(FLAGS) -T $(VENDOR_DIR)/Ld/Link.ld -nostartfiles -Xlinker --gc-sections -Wl,-Map,"$(BUILD_DIR)/CH32V307VCT6.map" --specs=nano.specs --specs=nosys.specs

FLASH_SIZE := 262144  # 256KB for CH32V307 (262144 bytes)
RAM_SIZE := 65536     # 64KB for CH32V307 (65536 bytes)

# Default target
all: $(BUILD_DIR)/$(TARGET_HEX)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "=== Memory Usage ==="
	@$(PREFIX)size -B $@ | tail -1 | awk '{ \
		flash_used = $$1 + $$2; \
		ram_used = $$2 + $$3; \
		flash_percent = (flash_used * 100) / $(FLASH_SIZE); \
		ram_percent = (ram_used * 100) / $(RAM_SIZE); \
		printf "Section sizes:\n"; \
		printf "  .text (Flash): %8d bytes\n", $$1; \
		printf "  .data:         %8d bytes\n", $$2; \
		printf "  .bss:          %8d bytes\n", $$3; \
		printf "\n"; \
		printf "Flash used: %d/%d bytes (%.1f%%)\n", flash_used, $(FLASH_SIZE), flash_percent; \
		printf "RAM used:   %d/%d bytes (%.1f%%)\n", ram_used, $(RAM_SIZE), ram_percent; \
	}'

$(BUILD_DIR)/$(TARGET_HEX): $(BUILD_DIR)/$(TARGET_EXEC)
	$(HEX) $< $@
	@echo "Hex file created: $@"

flash: $(BUILD_DIR)/$(TARGET_HEX)
	$(FLASH_PROG)  --chip CH32V30X flash $(BUILD_DIR)/$(TARGET_HEX)

usbflash: $(BUILD_DIR)/$(TARGET_EXEC)
	wchisp flash $<

# assembly
$(BUILD_DIR)/%.S.o: %.S
	$(MKDIR_P) $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean all size

# Additional target to check size only
size: $(BUILD_DIR)/$(TARGET_EXEC)

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
