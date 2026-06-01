CC = arm-none-eabi-gcc
MACH = cortex-m4
CFLAGS = -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -o0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_ls.ld -Wl,-Map=final.map
LDFLAGS_sh= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32_ls.ld -Wl,-Map=final.map

all:main.o stm32_startup_file.o syscalls.o final.elf

semi:main.o stm32_startup_file.o final_sh.elf
main.o:main1.c
	$(CC) $(CFLAGS) -o $@ $^
	
stm32_startup_file.o:stm32_startup_file.c
	$(CC) $(CFLAGS) -o $@ $^
	
syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^
	
final.elf:main.o stm32_startup_file.o syscalls.o
	$(CC) $(LDFLAGS) -o $@ $^

final_sh.elf:main.o stm32_startup_file.o
	$(CC) $(LDFLAGS_sh) -o $@ $^	

clean:
	rm -rf *.o *.elf
	
load:
	openocd -f board/st_nucleo_f4.cfg