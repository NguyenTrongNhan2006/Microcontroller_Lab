# Build và sử dụng source Lab 2

Target STM32F103C6: Flash 32 KB, RAM 10 KB; HSI 8 MHz.
Cần ARM GNU Toolchain (có trong STM32CubeIDE) và STM32CubeF1 V1.8.7.
HAL/CMSIS/startup lấy từ package ST đã cài, không đóng gói lại trong repo.

## Build

Chạy PowerShell trong thư mục `Source_Code`:

```powershell
# Tự tìm ARM GCC trong C:\ST\STM32CubeIDE_* và build đủ 10 bài
.\build.ps1
# Chọn bài và chỉ định đường dẫn nếu dùng máy khác
.\build.ps1 -Exercises 8,9,10 -FirmwareRoot 'C:\STM32Cube_FW_F1_V1.8.7' -CompilerBin 'C:\ArmToolchain\bin'
# Profile nhanh cho bài 8-10 (ghi ra thư mục riêng)
.\build.ps1 -Exercises 8,9,10 -TickMs 1 -ScanSlotMs 5 -MatrixSlotMs 1 -OutputDirectory '..\Firmware\fast'
```

Kết quả mặc định nằm ở `../Firmware/exercise01.hex` đến `exercise10.hex`,
cùng các ELF để debug (ELF được gitignore).
Script truyền `-DLAB2_ACTIVE_EXERCISE=N`, không cần sửa header từng lần.
Mặc định trong `Inc/lab2.h` là bài 1. Bài 1-4 cố định slot theo đề;
`ScanSlotMs` áp dụng cho bài 5-10. Ngắt TIM2 tick 1 ms của profile nhanh
cho phép 7 đoạn có frame 50 Hz và ma trận có frame 125 Hz.
Các HEX commit trong repo là **profile mặc định tick 10 ms**.

Đây là project build bằng script; không kèm `.ioc` hay `.project` CubeIDE.
Nếu ghép vào project CubeIDE, dùng các file ứng dụng trong Src/Inc và
đảm bảo không có hai main, hai callback, hai SysTick hoặc hai TIM2 handler.

## Cấu trúc

- `main.c`: HSI, GPIO, TIM2/NVIC và vòng lặp gọi `lab2_poll()`.
- `lab2.c`: chọn exercise, callback kiểm tra đúng instance TIM2.
- `exercise1.c` ... `exercise10.c`: init, phần chạy mỗi tick và foreground của từng bài.
- `display.c`: `display7SEG()`, `update7SEG()`, quét trong ISR cho bài 1-7.
- `clock.c`: HH:MM, thêm số 0 và chuyển ngày 23:59:59 -> 00:00:00.
- `software_timer.c`: timer mẫu một lần và 4 timer định kỳ độc lập.
- `services.c`: nhận sự kiện timer trong main để cập nhật clock/quét.
- `matrix.c`: buffer theo cột, chữ A và dịch vòng sang trái.
- `stm32f1xx_it.c`: TIM2 IRQ gọi HAL, SysTick duy trì HAL tick.

Trong main, phần buffer HH:MM được ghi trong critical section để ISR không
đọc một nửa giá trị cũ/mới. Counter/flag dùng `volatile`; thao tác lấy và xóa
sự kiện timer cũng có critical section, khôi phục trạng thái IRQ trước đó.
Timer định kỳ tự reload ở ISR, tích lũy số lần hết hạn; main chậm vẫn nhận
đủ giây clock. Quét bị lỡ slot sẽ nhảy tới slot hiện tại, không phát lại
cả loạt frame cũ. Trong vòng main vẫn cần phục vụ thường xuyên để LED đều.

`setTimer0(duration)` giữ phép chia nguyên giống giáo trình:
`setTimer0(1)` với tick 10 ms không phát cờ. API định kỳ
`timer_set_periodic(id, duration)` làm tròn lên để timeout không đến sớm.
`duration = 0` dừng timer định kỳ; id hợp lệ 0..3. Trong bài 8-10:
timer 0 = clock/DOT, timer 1 = 7 đoạn, timer 2 = ma trận, timer 3 = animation.
Bài 6 dùng timer0 mẫu cho LED và timer định kỳ 1 cho clock.

## Nạp và kết nối

Nạp đúng `exerciseNN.hex` vào STM32F103C6 của mạch cùng pin mapping ở
[README Lab 2](../README.md). Nối VDD/VDDA = +3.3 V, VSS/VSSA = GND,
BOOT0 = GND, thêm điện trở hạn dòng và mạch transistor phù hợp.
`main.c` tắt JTAG/SWD vì PA13..PA15 và PB3/PB4 dùng làm GPIO;
nạp bo thật có thể cần connect-under-reset.
Buffer ma trận: một byte cho mỗi cột, bit 0 là hàng trên cùng.
Bài 10 dịch vòng 8 cột, sau 8 bước trở lại chữ A ban đầu.
Clock là mô phỏng theo HSI/timer, không phải RTC được hiệu chuẩn.

## Host tests

```powershell
# Dùng GCC cho Windows, không dùng arm-none-eabi-gcc
.\Tests\test.ps1 -Compiler gcc
```

Test build riêng từng exercise với HAL/GPIO giả lập. Có kiểm tra thời điểm
chuyển digit/DOT/LED, HH:MM, rollover, blank-before-update, buffer A,
dịch vòng, timeout 1/10/1000 ms, bảo toàn bit GPIO và IRQ mask.
Bài 8-10 được kiểm tra không ghi GPIO từ ISR và không dùng HAL_Delay;
timer callback của instance khác bị bỏ qua. Test chỉ hỗ trợ profile mặc định.
Xem [VERIFICATION.md](VERIFICATION.md) để biết phạm vi đã kiểm chứng.
