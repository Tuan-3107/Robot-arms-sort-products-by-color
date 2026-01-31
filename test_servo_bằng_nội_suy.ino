/*
 * ============================================================================
 * TEST SERVO CHÂN ĐẾ - PHIÊN BẢN ĐỠN GIẢN
 * ============================================================================
 * 
 * Chức năng: Tự động quét liên tục 0° → 180° → 0° với nội suy tuyến tính
 * 
 * Không cần nhập lệnh, chỉ cần upload và xem!
 * 
 * ============================================================================
 */

#include <Servo.h>

// ============================================================================
// CẤU HÌNH
// ============================================================================

Servo servoBase;

#define SERVO_PIN 3      // Chân PWM kết nối servo
#define STEPS 40        // Số bước nội suy (30 = mượt vừa phải)
#define DELAY_MS 50      // Delay giữa các bước (ms)
#define PAUSE_MS 1000    // Dừng ở 2 đầu (ms)

// ============================================================================
// HÀM NỘI SUY TUYẾN TÍNH
// ============================================================================

void moveSmooth(int startAngle, int endAngle) {
    Serial.print("Di chuyển từ ");
    Serial.print(startAngle);
    Serial.print("° → ");
    Serial.print(endAngle);
    Serial.println("°");
    Serial.println("─────────────────────────────────────────");
    
    for (int step = 0; step <= STEPS; step++) {
        // *** CÔNG THỨC NỘI SUY ***
        float progress = (float)step / (float)STEPS;
        int angle = startAngle + (endAngle - startAngle) * progress;
        
        // Gửi lệnh đến servo
        servoBase.write(angle);
        
        // In ra mỗi 5 bước
        if (step % 5 == 0 || step == STEPS) {
            Serial.print("  Bước ");
            Serial.print(step);
            Serial.print("/");
            Serial.print(STEPS);
            Serial.print(" → ");
            Serial.print(angle);
            Serial.println("°");
        }
        
        delay(DELAY_MS);
    }
    
    Serial.println("✓ Hoàn thành!");
    Serial.println();
}

// ============================================================================
// SETUP
// ============================================================================

void setup() {
    Serial.begin(9600);
    
    Serial.println("\n\n╔═══════════════════════════════════════════╗");
    Serial.println("║  TEST SERVO CHÂN ĐẾ - AUTO SWEEP        ║");
    Serial.println("╚═══════════════════════════════════════════╝");
    Serial.println();
    
    servoBase.attach(SERVO_PIN);
    servoBase.write(90);  // Vị trí giữa
    
    Serial.println("[INIT] Servo sẵn sàng!");
    Serial.println();
    
    delay(2000);
}

// ============================================================================
// LOOP - TỰ ĐỘNG QUÉT LIÊN TỤC
// ============================================================================

void loop() {
    // Quét từ 0° → 180°
    Serial.println("\n═══ QUÉT: 0° → 180° ═══");
    moveSmooth(0, 180);
    delay(PAUSE_MS);  // Dừng 1 giây
    
    // Quét từ 180° → 0°
    Serial.println("\n═══ QUÉT: 180° → 0° ═══");
    moveSmooth(180, 0);
    delay(PAUSE_MS);  // Dừng 1 giây
    
    // Lặp lại...
}

// ============================================================================
// GIẢI THÍCH
// ============================================================================

/*
 * CÔNG THỨC NỘI SUY TUYẾN TÍNH:
 * 
 *   angle = start + (end - start) × (step / total_steps)
 * 
 * VÍ DỤ: Di chuyển từ 0° đến 180° với 30 bước
 * 
 *   Bước 0:  angle = 0 + (180-0) × (0/30)  = 0°
 *   Bước 10: angle = 0 + (180-0) × (10/30) = 60°
 *   Bước 20: angle = 0 + (180-0) × (20/30) = 120°
 *   Bước 30: angle = 0 + (180-0) × (30/30) = 180°
 * 
 * ĐIỀU CHỈNH THAM SỐ:
 * 
 *   STEPS = 10:  Nhanh, hơi giật
 *   STEPS = 30:  Cân bằng (KHUYẾN NGHỊ)
 *   STEPS = 60:  Rất mượt, chậm
 * 
 *   DELAY_MS = 20:  Nhanh
 *   DELAY_MS = 50:  Vừa phải (KHUYẾN NGHỊ)
 *   DELAY_MS = 100: Chậm, dễ quan sát
 * 
 */
