/*
 * MANUAL CONTROL - TÌM VỊ TRÍ CHO 6 SERVO
 * Dùng lệnh để điều khiển từng servo → lưu vị trí
 */

#include <Servo.h>

Servo servo1, servo2, servo3, servo4, servo5, servo6;

#define SERVO1_PIN 3
#define SERVO2_PIN 5
#define SERVO3_PIN 6
#define SERVO4_PIN 9
#define SERVO5_PIN 10
#define SERVO6_PIN 11

// Lưu vị trí hiện tại
int pos[6] = {90, 90, 90, 90, 90, 90};

void setup() {
    Serial.begin(9600);
    
    Serial.println("\n╔════════════════════════════════════════════════╗");
    Serial.println("║     MANUAL CONTROL - TÌM VỊ TRÍ 6 SERVO       ║");
    Serial.println("╚════════════════════════════════════════════════╝");
    Serial.println();
    Serial.println("CÚ PHÁP: <servo><góc>");
    Serial.println();
    Serial.println("VÍ DỤ:");
    Serial.println("  1090  → Servo 1 (Base) = 90°");
    Serial.println("  2120  → Servo 2 (Shoulder) = 120°");
    Serial.println("  3060  → Servo 3 (Elbow) = 60°");
    Serial.println("  4090  → Servo 4 (Wrist Rot) = 90°");
    Serial.println("  5110  → Servo 5 (Wrist Pitch) = 110°");
    Serial.println("  6030  → Servo 6 (Gripper) = 30° (KẸP)");
    Serial.println("  6090  → Servo 6 (Gripper) = 90° (MỞ)");
    Serial.println();
    Serial.println("LỆNH ĐẶC BIỆT:");
    Serial.println("  P  → In vị trí hiện tại (copy vào code)");
    Serial.println("  H  → Về HOME (90° tất cả)");
    Serial.println();
    Serial.println("⚠️ GHI NHỚ: Gripper 30°=KẸP, 90°=MỞ");
    Serial.println("═════════════════════════════════════════════════");
    Serial.println();
    
    // Attach và đưa về vị trí HOME
    servo1.attach(SERVO1_PIN);
    servo2.attach(SERVO2_PIN);
    servo3.attach(SERVO3_PIN);
    servo4.attach(SERVO4_PIN);
    servo5.attach(SERVO5_PIN);
    servo6.attach(SERVO6_PIN);
    
    servo1.write(pos[0]);
    servo2.write(pos[1]);
    servo3.write(pos[2]);
    servo4.write(pos[3]);
    servo5.write(pos[4]);
    servo6.write(pos[5]);
    
    delay(1000);
    
    Serial.println("✓ Sẵn sàng! Nhập lệnh:");
    printCurrentPos();
    Serial.println();
}

void loop() {
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        
        if (cmd == "P" || cmd == "p") {
            printCode();
        }
        else if (cmd == "H" || cmd == "h") {
            Serial.println("→ Về HOME (90° tất cả)");
            for (int i = 0; i < 6; i++) {
                pos[i] = 90;
            }
            servo1.write(90);
            servo2.write(90);
            servo3.write(90);
            servo4.write(90);
            servo5.write(90);
            servo6.write(90);
            printCurrentPos();
        }
        else if (cmd.length() >= 2) {
            int servoNum = cmd.substring(0, 1).toInt();
            int angle = cmd.substring(1).toInt();
            
            if (servoNum >= 1 && servoNum <= 6 && angle >= 0 && angle <= 180) {
                pos[servoNum - 1] = angle;
                
                switch(servoNum) {
                    case 1: servo1.write(angle); Serial.print("✓ Servo 1 (Base) → "); break;
                    case 2: servo2.write(angle); Serial.print("✓ Servo 2 (Shoulder) → "); break;
                    case 3: servo3.write(angle); Serial.print("✓ Servo 3 (Elbow) → "); break;
                    case 4: servo4.write(angle); Serial.print("✓ Servo 4 (Wrist Rot) → "); break;
                    case 5: servo5.write(angle); Serial.print("✓ Servo 5 (Wrist Pitch) → "); break;
                    case 6: 
                        servo6.write(angle);
                        Serial.print("✓ Servo 6 (Gripper) → ");
                        break;
                }
                
                Serial.print(angle);
                Serial.print("°");
                
                if (servoNum == 6) {
                    if (angle >= 25 && angle <= 35) {
                        Serial.println(" (KẸP)");
                    } else if (angle >= 85 && angle <= 95) {
                        Serial.println(" (MỞ)");
                    } else {
                        Serial.println();
                    }
                } else {
                    Serial.println();
                }
                
                delay(300);
            }
            else {
                Serial.println("❌ Lỗi: Servo 1-6, góc 0-180");
            }
        }
        else {
            Serial.println("❌ Lệnh không hợp lệ! (Nhập P để xem vị trí)");
        }
        
        Serial.println();
    }
}

void printCurrentPos() {
    Serial.println("─────────────────────────────────────────────────");
    Serial.print("Vị trí hiện tại: [");
    Serial.print(pos[0]); Serial.print(", ");
    Serial.print(pos[1]); Serial.print(", ");
    Serial.print(pos[2]); Serial.print(", ");
    Serial.print(pos[3]); Serial.print(", ");
    Serial.print(pos[4]); Serial.print(", ");
    Serial.print(pos[5]); Serial.println("]");
    Serial.println("─────────────────────────────────────────────────");
}

void printCode() {
    Serial.println();
    Serial.println("┌──────────────────────────────────────────────┐");
    Serial.println("│          VỊ TRÍ HIỆN TẠI CỦA ROBOT           │");
    Serial.println("├──────────────────────────────────────────────┤");
    Serial.print("│ Servo 1 (Base):         ");
    if (pos[0] < 100) Serial.print(" ");
    if (pos[0] < 10) Serial.print(" ");
    Serial.print(pos[0]);
    Serial.println("°                   │");
    
    Serial.print("│ Servo 2 (Shoulder):     ");
    if (pos[1] < 100) Serial.print(" ");
    if (pos[1] < 10) Serial.print(" ");
    Serial.print(pos[1]);
    Serial.println("°                   │");
    
    Serial.print("│ Servo 3 (Elbow):        ");
    if (pos[2] < 100) Serial.print(" ");
    if (pos[2] < 10) Serial.print(" ");
    Serial.print(pos[2]);
    Serial.println("°                   │");
    
    Serial.print("│ Servo 4 (Wrist Rot):    ");
    if (pos[3] < 100) Serial.print(" ");
    if (pos[3] < 10) Serial.print(" ");
    Serial.print(pos[3]);
    Serial.println("°                   │");
    
    Serial.print("│ Servo 5 (Wrist Pitch):  ");
    if (pos[4] < 100) Serial.print(" ");
    if (pos[4] < 10) Serial.print(" ");
    Serial.print(pos[4]);
    Serial.println("°                   │");
    
    Serial.print("│ Servo 6 (Gripper):      ");
    if (pos[5] < 100) Serial.print(" ");
    if (pos[5] < 10) Serial.print(" ");
    Serial.print(pos[5]);
    Serial.print("°");
    if (pos[5] >= 25 && pos[5] <= 35) {
        Serial.println(" (KẸP)          │");
    } else if (pos[5] >= 85 && pos[5] <= 95) {
        Serial.println(" (MỞ)           │");
    } else {
        Serial.println("                │");
    }
    Serial.println("└──────────────────────────────────────────────┘");
    Serial.println();
    
    Serial.println("═══════ CODE ĐỂ COPY VÀO CODE CHÍNH ═══════");
    Serial.println();
    Serial.println("RobotPosition YOUR_POS = {");
    Serial.print("    "); Serial.print(pos[0]); Serial.println(", // base");
    Serial.print("    "); Serial.print(pos[1]); Serial.println(", // shoulder");
    Serial.print("    "); Serial.print(pos[2]); Serial.println(", // elbow");
    Serial.print("    "); Serial.print(pos[3]); Serial.println(", // wristRot");
    Serial.print("    "); Serial.print(pos[4]); Serial.println(", // wristPitch");
    Serial.print("    "); Serial.print(pos[5]); Serial.println("  // gripper (30=kẹp, 90=mở)");
    Serial.println("};");
    Serial.println();
    Serial.println("════════════════════════════════════════════════");
    Serial.println();
}
