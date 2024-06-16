#include <Arduino.h>
#include <array>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

const int PIN_TO_TEST = 13;
const int ARRAY_SIZE = 1024;

void benchmark_operation(void (*operation)(), const char* name) {
    unsigned long start_time = micros();
    operation();
    unsigned long duration = micros() - start_time;
    Serial.print("{\"name\": \"");
    Serial.print(name);
    Serial.print("\", \"duration\": ");
    Serial.print(duration);
    Serial.println("}");
}

void fill_array_random(std::array<int, ARRAY_SIZE>& arr, int max_value = -1) {
    if (max_value == -1) {
        max_value = arr.size() - 1;
    }

    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = random(0, max_value + 1);
    }
}

void benchmark_sort_array(std::array<int, ARRAY_SIZE>& arr, void (*sort_function)(std::array<int, ARRAY_SIZE>&), const char* sort_name) {
    unsigned long start_time = micros();
    sort_function(arr);
    unsigned long duration = micros() - start_time;
    Serial.print("{\"name\": \"sortArray_");
    Serial.print(sort_name);
    Serial.print("\", \"duration\": ");
    Serial.print(duration);
    Serial.println("}");
}

void bubble_sort(std::array<int, ARRAY_SIZE>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <std::size_t ARRAY_SIZE>
void quick_sort(std::array<int, ARRAY_SIZE>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = arr[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (arr[i] < pivot) {
            ++i;
        }
        while (arr[j] > pivot) {
            --j;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }

    if (left < j) {
        quick_sort(arr, left, j);
    }
    if (i < right) {
        quick_sort(arr, i, right);
    }
}

template <std::size_t ARRAY_SIZE>
void quick_sort(std::array<int, ARRAY_SIZE>& arr) {
    quick_sort(arr, 0, arr.size() - 1);
}

template <std::size_t ARRAY_SIZE>
void counting_sort(std::array<int, ARRAY_SIZE>& arr) {
    int max_value = *std::max_element(arr.begin(), arr.end());

    std::vector<int> count(ARRAY_SIZE, 0);

    for (int num : arr) {
        if (num < 0 || num >= ARRAY_SIZE) {
            continue;
        }
        ++count[num];
    }

    int index = 0;
    for (int num = 0; num <= max_value; ++num) {
        while (count[num] > 0) {
            arr[index++] = num;
            --count[num];
        }
    }
}

void operation_digital_read() {
    digitalRead(PIN_TO_TEST);
}

void benchmark_digital_read() {
    benchmark_operation(operation_digital_read, "digitalRead");
}

void operation_digital_write() {
    digitalWrite(PIN_TO_TEST, HIGH);
    digitalWrite(PIN_TO_TEST, LOW);
}

void benchmark_digital_write() {
    benchmark_operation(operation_digital_write, "digitalWrite");
}

void operation_pin_mode() {
    pinMode(PIN_TO_TEST, OUTPUT);
}

void benchmark_pin_mode() {
    benchmark_operation(operation_pin_mode, "pinMode");
}

void operation_multiply_byte() {
    byte a = 10;
    byte b = 5;
    byte result = a * b;
}

void benchmark_multiply_byte() {
    benchmark_operation(operation_multiply_byte, "multiply byte");
}

void operation_divide_byte() {
    byte a = 10;
    byte b = 5;
    byte result = a / b;
}

void benchmark_divide_byte() {
    benchmark_operation(operation_divide_byte, "divide byte");
}

void operation_add_byte() {
    byte a = 10;
    byte b = 5;
    byte result = a + b;
}

void benchmark_add_byte() {
    benchmark_operation(operation_add_byte, "add byte");
}

void operation_multiply_integer() {
    int a = 1000;
    int b = 5;
    int result = a * b;
}

void benchmark_multiply_integer() {
    benchmark_operation(operation_multiply_integer, "multiply integer");
}

void operation_divide_integer() {
    int a = 1000;
    int b = 5;
    int result = a / b;
}

void benchmark_divide_integer() {
    benchmark_operation(operation_divide_integer, "divide integer");
}

void operation_add_integer() {
    int a = 1000;
    int b = 5;
    int result = a + b;
}

void benchmark_add_integer() {
    benchmark_operation(operation_add_integer, "add integer");
}

void operation_multiply_long() {
    long a = 1000000;
    long b = 5;
    long result = a * b;
}

void benchmark_multiply_long() {
    benchmark_operation(operation_multiply_long, "multiply long");
}

void operation_divide_long() {
    long a = 1000000;
    long b = 5;
    long result = a / b;
}

void benchmark_divide_long() {
    benchmark_operation(operation_divide_long, "divide long");
}

void operation_add_long() {
    long a = 1000000;
    long b = 5;
    long result = a + b;
}

void benchmark_add_long() {
    benchmark_operation(operation_add_long, "add long");
}

void operation_multiply_float() {
    float a = 3.14;
    float b = 2.0;
    float result = a * b;
}

void benchmark_multiply_float() {
    benchmark_operation(operation_multiply_float, "multiply float");
}

void operation_divide_float() {
    float a = 3.14;
    float b = 2.0;
    float result = a / b;
}

void benchmark_divide_float() {
    benchmark_operation(operation_divide_float, "divide float");
}

void operation_add_float() {
    float a = 3.14;
    float b = 2.0;
    float result = a + b;
}

void benchmark_add_float() {
    benchmark_operation(operation_add_float, "add float");
}

void operation_itoa() {
    int num = 12345;
    char buf[16];
    itoa(num, buf, 10);
}

void benchmark_itoa() {
    benchmark_operation(operation_itoa, "itoa()");
}

void operation_ltoa() {
    long num = 1234567890;
    char buf[32];
    ltoa(num, buf, 10);
}

void benchmark_ltoa() {
    benchmark_operation(operation_ltoa, "ltoa()");
}

void operation_dtostrf() {
    float num = 123.456;
    char buf[16];
    dtostrf(num, 7, 3, buf);
}

void benchmark_dtostrf() {
    benchmark_operation(operation_dtostrf, "dtostrf()");
}

void operation_random() {
    random(0, 100);
}

void benchmark_random() {
    benchmark_operation(operation_random, "random()");
}

void operation_bit_operations() {
    byte x = 3;
    byte y = 0;
    y |= (1 << x);
}

void benchmark_bit_operations() {
    benchmark_operation(operation_bit_operations, "y |= (1<<x)");
}

void operation_analog_read() {
    analogRead(PIN_TO_TEST);
}

void benchmark_analog_read() {
    benchmark_operation(operation_analog_read, "analogRead");
}

void operation_pwm_write() {
    analogWrite(PIN_TO_TEST, 512);
}

void benchmark_pwm_write() {
    benchmark_operation(operation_pwm_write, "analogWrite() PWM");
}

void operation_delay() {
    delay(1);
}

void benchmark_delay() {
    benchmark_operation(operation_delay, "delay(1)");
}

void operation_delay_100() {
    delay(100);
}

void benchmark_delay_100() {
    benchmark_operation(operation_delay_100, "delay(100)");
}

void operation_delay_microseconds_2() {
    delayMicroseconds(2);
}

void benchmark_delay_microseconds_2() {
    benchmark_operation(operation_delay_microseconds_2, "delayMicroseconds(2)");
}

void operation_delay_microseconds_5() {
    delayMicroseconds(5);
}

void benchmark_delay_microseconds_5() {
    benchmark_operation(operation_delay_microseconds_5, "delayMicroseconds(5)");
}

void operation_delay_microseconds_100() {
    delayMicroseconds(100);
}

void benchmark_delay_microseconds_100() {
    benchmark_operation(operation_delay_microseconds_100, "delayMicroseconds(100)");
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Uncomment below to test with a random array
    // std::array<int, ARRAY_SIZE> test_array;
    // fill_array_random(test_array);

    std::array<int, ARRAY_SIZE> test_array = {254, 448, 645, 780, 847, 178, 845, 37, 169, 150, 1018, 515, 239, 789, 661, 661, 375, 897, 461, 270, 943, 86, 38, 644, 42, 45, 296, 276, 441, 242, 524, 49, 66, 694, 521, 750, 507, 665, 149, 182, 622, 205, 161, 932, 912, 435, 333, 250, 76, 798, 389, 411, 544, 156, 650, 959, 747, 861, 285, 136, 1003, 129, 556, 666, 175, 620, 825, 975, 945, 767, 394, 797, 797, 553, 766, 552, 268, 919, 514, 292, 348, 23, 231, 116, 874, 604, 949, 530, 995, 508, 983, 927, 426, 519, 359, 962, 694, 88, 929, 320, 292, 645, 338, 435, 508, 474, 478, 489, 384, 214, 32, 613, 761, 614, 495, 545, 911, 190, 75, 739, 789, 184, 80,877, 994, 931, 26, 907, 590, 31, 804, 784, 538, 809, 667, 845, 709, 973, 1020, 640, 599, 73, 653, 909, 457, 692, 786, 1007, 174, 340, 622, 756, 524, 994, 456, 534, 631, 241, 93, 562, 132, 661, 170, 877, 337, 533, 304, 718, 416, 223, 525, 551, 143, 993, 615, 181, 587, 595, 855, 807, 547, 908, 326, 781, 509,0, 365, 948, 556, 1017, 949, 748, 262, 690, 232, 16, 496, 170, 709, 893, 1014, 50, 580, 566, 172, 603, 112, 715, 650, 619, 457, 487, 629, 644, 797, 1007, 898, 353, 183, 146, 367, 69, 36, 332, 606, 694, 483, 132, 345, 634, 492, 583, 807, 295, 48, 790, 964, 373, 729, 182, 997, 825, 414, 1011, 221, 445, 500, 785, 164, 719, 339, 685, 438, 435, 683, 428, 598, 383, 1013, 775, 813, 418, 330, 14, 263, 618, 927, 958, 552, 182, 795, 355, 426, 464, 491, 104, 412, 1021, 434, 964, 718, 212, 555, 67, 796, 821, 836, 545, 149, 753, 184, 689, 341, 321, 715, 377, 408, 991, 603, 403, 371, 761, 872, 177, 226, 675, 709, 880, 684,467, 390, 28, 9, 360, 74, 522, 509, 603, 854, 1021, 1022, 878, 944, 349, 50, 966, 857, 703, 41, 996, 297, 183, 320, 497, 372, 221, 432, 1014, 616, 274, 909, 236, 970, 478, 772, 990, 752, 869, 714, 906, 556, 61, 858, 195, 369, 801, 554, 264, 610, 411, 312, 163, 275, 738, 1014, 87, 656, 903, 641, 771, 109, 487, 370, 493, 632, 546, 1010, 608, 119, 750, 677, 393, 887, 400, 1002, 597, 734, 933, 652, 620, 75, 538, 304, 115, 571, 981, 971, 421, 261, 88, 736, 624, 341, 501, 172, 108, 933, 243, 986, 774, 455, 927, 873, 488, 122, 212, 769, 902, 669, 322, 301, 159, 936, 359, 24, 291, 268, 921, 900, 573, 44, 225, 489, 562, 599, 741, 588, 791, 634, 295, 767, 917, 815, 594, 224, 248, 675, 841, 575, 381, 554, 308, 716, 964, 513, 763, 750, 810, 349, 373, 26, 62, 342, 959, 866, 698, 886, 88, 926, 145, 973, 159, 720, 865, 702, 70, 302, 916, 766, 654, 568, 1010, 899, 1017, 854, 691, 817, 994, 497, 961, 805, 689, 10, 37, 23, 30,38, 637, 251, 424, 969, 909, 472, 906, 152, 542, 919, 154, 61, 805, 539, 389, 865, 495, 845, 912, 105, 650, 29, 249, 627, 573, 613, 248, 269, 697, 212, 768, 971, 590, 576, 449, 447, 463, 870, 340, 336, 461, 502, 949, 844, 67, 70, 290, 543, 789, 132, 173, 604, 885, 198, 731, 558, 58, 925, 80, 652, 631, 277,159, 395, 998, 423, 15, 281, 913, 1023, 885, 296, 383, 380, 928, 478, 497, 992, 420, 257, 230, 105, 323, 337, 717, 416, 101, 769, 370, 992, 98, 330, 160, 655, 878, 465, 335, 751, 557, 213, 823, 300, 321, 420, 311, 33, 404, 42, 303, 582, 136, 260, 161, 309, 135, 892, 521, 471, 137, 481, 261, 452, 40, 30, 946, 64, 200, 215, 44, 626, 199, 72, 851, 5, 764, 824, 209, 153, 689, 953, 645, 701, 314, 453, 52, 147, 390, 68, 215, 306, 352, 205, 181, 952, 906, 785, 85, 834, 335, 240, 722, 0, 698, 656, 685, 269, 72, 670, 86, 833, 300, 247, 1009, 498, 537, 975, 862, 4, 56, 563, 574, 461, 848, 438, 205, 58, 685, 433, 664, 74, 7, 807, 197, 682, 902, 391, 256, 732, 641, 162, 771, 804, 513, 1020, 47, 495, 430, 777, 220, 478, 325, 258, 692, 201, 950, 831, 1023, 749, 41, 69, 894, 369, 781, 705, 824, 687, 477, 999, 472, 746, 752, 107, 419, 823, 318, 241, 634, 365, 985, 703, 900, 702, 16, 544, 554, 769, 935, 708, 879, 566, 12, 338,266, 208, 245, 170, 492, 1013, 374, 506, 345, 320, 218, 708, 138, 793, 159, 421, 211, 268, 359, 81, 420, 484, 995, 37, 919, 496, 314, 107, 401, 183, 221, 780, 175, 850, 933, 421, 343, 497, 699, 975, 515, 600, 162, 453, 62, 624, 134, 1011, 747, 37, 932, 45, 799, 511, 778, 660, 928, 431, 193, 909, 230, 681, 570, 310, 262, 215, 259, 251, 542, 169, 117, 702, 702, 197, 272, 680, 217, 730, 571, 294, 394, 325, 192, 241, 244, 536, 374, 506, 167, 21, 978, 700, 183, 446, 557, 817, 785, 364, 291, 38, 695, 1014, 369, 586, 719, 86, 894, 228, 897, 155, 644, 34, 635, 517, 300, 120, 981, 822, 920, 72, 364, 165, 87, 192, 761,472, 538, 366, 386, 490, 813, 935, 194, 1021, 136, 48, 763, 331, 284, 727, 176, 5, 944, 413, 788, 1011, 488, 42, 725, 47, 862, 795, 24, 315, 635, 454, 42, 272, 495, 1014, 935, 618, 912, 531, 748, 777, 253, 866, 637, 830, 690, 625, 967, 879, 821, 795, 542, 397, 157, 658, 725, 334, 272, 918, 391, 469, 122, 442, 625, 168, 20, 485, 645, 708, 138, 540, 478, 710, 725, 369, 731, 906, 938, 975, 888, 432, 674, 84, 525, 343, 761, 443, 649, 799, 279, 496, 488, 39, 901, 921, 305, 794, 390, 555, 905, 342, 701, 357, 172, 1010, 422, 854, 33, 140, 889, 131, 930, 89, 112, 482, 436, 55, 316, 924, 66, 390, 143, 19, 952, 972, 377, 1003, 674, 221, 841, 1002, 147, 482, 257, 333, 636, 831, 70, 632, 548, 430, 59, 143, 459, 67, 513, 933, 886, 414, 267};

    benchmark_digital_read();
    benchmark_digital_write();
    benchmark_pin_mode();
    benchmark_multiply_byte();
    benchmark_divide_byte();
    benchmark_add_byte();
    benchmark_multiply_integer();
    benchmark_divide_integer();
    benchmark_add_integer();
    benchmark_multiply_long();
    benchmark_divide_long();
    benchmark_add_long();
    benchmark_multiply_float();
    benchmark_divide_float();
    benchmark_add_float();
    benchmark_itoa();
    benchmark_ltoa();
    benchmark_dtostrf();
    benchmark_random();
    benchmark_bit_operations();
    benchmark_analog_read();
    benchmark_pwm_write();
    benchmark_delay();
    benchmark_delay_100();
    benchmark_delay_microseconds_2();
    benchmark_delay_microseconds_5();
    benchmark_delay_microseconds_100();

    benchmark_sort_array(test_array, bubble_sort, "bubble");
    benchmark_sort_array(test_array, quick_sort, "quick");
    benchmark_sort_array(test_array, counting_sort, "counting");
}

void loop() {
}