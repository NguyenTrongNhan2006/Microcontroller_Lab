# Lab 1 — Source hoàn chỉnh Exercise 1–10

Target: **STM32F103C6**, HSI **8 MHz**, Flash 32 KB, RAM 10 KB.
Các LED và LED 7 đoạn anode chung đều **active LOW** (GPIO = 0 bật).
`Src/main.c` chọn đúng một bài bằng `LAB1_ACTIVE_EXERCISE` (1–10).

## Build trên Windows

Cần ARM GNU Toolchain (có trong STM32CubeIDE) và STM32CubeF1 **V1.8.7**.
HAL/CMSIS/startup được lấy từ package ST đã cài, không đóng gói lại ở đây.
Chạy trong thư mục `Source_Code`:

```powershell
# Build cả 10 bài; tự tìm compiler trong C:\ST\STM32CubeIDE_*
.\build.ps1
# Hoặc chỉ định đường dẫn và chọn bài
.\build.ps1 -FirmwareRoot 'C:\STM32Cube_FW_F1_V1.8.7' -CompilerBin 'C:\ArmToolchain\bin' -Exercises 1,5,10
```

Kết quả: `../Firmware/exercise01.hex` đến `exercise10.hex` và ELF tương ứng.
Script truyền `-DLAB1_ACTIVE_EXERCISE=N`, ghi đè giá trị mặc định trong header.
Không cần tự sửa header để build từng bài. Bộ source này dùng script build,
**không phải project CubeIDE có sẵn `.ioc`/`.project`**.

Nếu tích hợp vào project CubeIDE tự tạo cho STM32F103C6: thêm các file
`Src/exercise*.c`, `Inc/exercises.h`, dùng cùng cấu hình GPIO/HSI và SysTick;
không thêm hai bản `main.c`, `SysTick_Handler` hay startup vào cùng một project.

## Hành vi và chân nối

| Bài | Hành vi |
| --- | --- |
| 1 | PA5 đỏ / PA6 vàng luân phiên, mỗi trạng thái 2 giây |
| 2 | PA5 đỏ 5 giây → PA7 xanh 3 giây → PA6 vàng 2 giây |
| 3 | Bắc–Nam xanh 3 giây, vàng 2 giây; sau đó Đông–Tây xanh 3 giây, vàng 2 giây; hướng còn lại đỏ |
| 4 | Hiển thị 0–9, đổi mỗi giây; PB0..PB6 = a..g |
| 5 | Bốn pha như bài 3; một LED 7 đoạn đếm thời gian còn lại **của pha toàn giao lộ**: 3,2,1 / 2,1 / 3,2,1 / 2,1 |
| 6 | PA4..PA15 sáng lần lượt, mỗi LED 500 ms |
| 7 | `clearAllClock()` tắt toàn bộ 12 LED |
| 8 | `setNumberOnClock(0..11)` bật vị trí tương ứng; demo bật tích lũy mỗi 500 ms |
| 9 | `clearNumberOnClock(0..11)` tắt vị trí tương ứng; demo bật hết rồi tắt lần lượt mỗi 500 ms |
| 10 | Đồng hồ bắt đầu 10:58:00, cập nhật mỗi giây và quay vòng 12 giờ |

Chân cho bài 3/5 (thứ tự **đỏ / vàng / xanh**):

| Hướng | Chân |
| --- | --- |
| Bắc | PA4 / PA5 / PA6 |
| Đông | PA7 / PA8 / PA9 |
| Nam | PA10 / PA11 / PA12 |
| Tây | PA13 / PA14 / PA15 |

Chân cho bài 6–10: vị trí 0 (12 giờ) = PA4, vị trí 1 = PA5, …,
vị trí 11 = PA15, xếp theo chiều kim đồng hồ. Bài 10 dùng `hour % 12`,
`minute / 5`, `second / 5`. Khi các kim trùng nhau, chỉ có **1–3 LED khác
nhau** sáng; không bật thêm LED sai vị trí chỉ để đủ ba đèn.
Đây là demo dùng `HAL_Delay`, không phải đồng hồ RTC chính xác dài hạn.

Chú ý bài 5 không phải bộ đếm 5 giây đỏ cho riêng một hướng: màn hình duy
nhất hiển thị thời gian tới lần chuyển pha kế tiếp của toàn giao lộ.

## Lưu ý phần cứng / Proteus

- Mỗi LED/segment cần điện trở hạn dòng riêng, ví dụ 330 ohm.
- Anode nối +3.3 V; cathode qua điện trở về GPIO.
- Nối VDD/VDDA = +3.3 V, VSS/VSSA = GND; BOOT0 kéo xuống GND.
- `main.c` tắt JTAG/SWD để giải phóng PA13..PA15 và PB3/PB4. Khi nạp
  bo thật, có thể cần connect-under-reset để kết nối lại debugger.
- Sơ đồ bài 1/2 **khác** mapping bài 3/5. Chọn đúng mạch và đúng HEX.
- `display7SEG()` nhận giá trị ngoài 0..9 sẽ tắt các segment;
  các hàm clock nhận vị trí ngoài 0..11 sẽ không thay đổi GPIO.

## Kiểm thử

```powershell
# GCC chạy trên máy Windows, không dùng arm-none-eabi-gcc ở bước này
.\Tests\test.ps1 -Compiler gcc
```

Test biên dịch chính các file exercise với GPIO/HAL_Delay giả lập, kiểm tra
120 trạng thái của mỗi bài 1–9 và 43.201 trạng thái bài 10 (đủ một vòng 12 giờ).
Có kiểm tra mask chữ số, vị trí clock, đầu vào không hợp lệ và bảo toàn GPIO
ngoài phạm vi sử dụng. Xem `VERIFICATION.md` để biết kết quả thực tế.
Host test không thay thế kiểm chứng mạch điện, thời gian thực hay Proteus.
