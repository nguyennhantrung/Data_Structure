1️⃣ Cốt lõi về Embedded Software Development (C/C++)

Vì JD nhấn mạnh C/C++ và secure coding, bạn cần chắc chắn nắm vững:

Memory Layout
    High Address
    +----------------------+ <- Stack grows xuống
    |      Stack           | <- Biến local, function call, return address
    +----------------------+
    |      Heap            | <- Dynamic memory (new, malloc)
    +----------------------+
    |      BSS             | <- Biến global/static chưa khởi tạo (default 0)
    +----------------------+
    |      Data Segment    | <- Biến global/static đã khởi tạo
    |       (.data)        |
    +----------------------+
    |      Text Segment    | <- Code chương trình (.text)
    |       (.text)        |
    +----------------------+
    Low Address

Pointer & Memory Management

con trỏ, reference, con trỏ hàm (function pointer – giống yêu cầu bài challenge).
Unique_ptr:  
    - MoveConstructible and MoveAssignable, 
    - but of neither CopyConstructible nor CopyAssignable.
    - get
    - reset
    - make_unique<type>()
    - use cases:
      - unique resource
      - factory function
Shared_ptr:
    - MoveConstructible and MoveAssignable, 
    - meet the requirements of CopyConstructible, CopyAssignable
    - get
    - reset
    - use_count
    - use cases:
      - shared resource
      - linked list
      - cache
Weak_prt:
    - MoveConstructible and MoveAssignable, 
    - meet the requirements of CopyConstructible, CopyAssignable
    - use_count()
    - lock()
    - expired()
    - use cases:
      - Circular References
      - Cache và Observer Pattern


cấp phát động (malloc/free, new/delete) và các lỗi memory (dangling pointer, double free, memory leak).
  dangling pointer: not set pointer to NULL after free => unexpected behavior
  double free: delete/free on a pointer
  memory leak: forget to delete/free memory

Struct & Union

packing, alignment, cách xử lý raw data (như sensor data 4 bytes).
  struct __attribute__((packed)) struct_name {};
  can be used in both struct and class 

bitfield (có thể hỏi nếu liên quan đến register/memory-mapped IO).
  - declare num of bit for a variable
  - if declare as 1 bit, it should be only 1 or 0
  - if 2 bits, it can be in range of 0 to 3
  - bitfield cannot be fload, double or pointer
  - bitfield can be pointed by pointer
  - 
  struct Flags {
    unsigned int a : 1; // 1 bit
    unsigned int b : 3; // 3 bit
    unsigned int c : 4; // 4 bit
  };

  int main() {
      struct Flags f;
      f.a = 1;
      f.b = 5;
      f.c = 10;

      printf("Size of struct Flags: %zu\n", sizeof(f)); // Thường 2 bytes
      printf("a=%u, b=%u, c=%u\n", f.a, f.b, f.c);
  }

Function Pointer & Callbacks

định nghĩa, gán, và gọi function pointer từ struct/class.

Type Casting
  1. static_cast
  - Chuyển đổi các kiểu dữ liệu cơ bản: int ↔ double, float ↔ int.
  - Chuyển kiểu upcast (Derived → Base) an toàn.
  - Chuyển kiểu downcast (Base → Derived) chỉ khi chắc chắn object thực sự là Derived.
  2. dynamic_cast
  - Chỉ dùng với pointer hoặc reference đến class polymorphic (có virtual function).
  - Downcast an toàn: Base* → Derived*
  - Kiểm tra tại runtime: nếu object không phải Derived → trả về nullptr (pointer) hoặc throw exception (reference).
  3. const_cast
  - Thêm hoặc bỏ const/volatile
  - Khi cần gọi hàm non-const nhưng dữ liệu thực sự có thể thay đổi.
  4. reinterpret_cast
  - Chuyển đổi kiểu bất kỳ, đặc biệt là pointer ↔ pointer hoặc pointer ↔ integer.
  - Thường dùng trong low-level programming, hardware access, serialization.

reinterpret_cast, static_cast, const_cast – đặc biệt khi parse data từ uint8_t[4] sang int/float.

Template / Generic Programming

vì bài challenge 2 yêu cầu vector generic -> nên ôn template<class T>.

-------------------------------------
2️⃣ Kiến thức Hệ thống & OS

JD có nhắc đến Linux, QNX, POSIX OS, Hypervisor ⇒ cần chuẩn bị:

Process vs Thread

pthread:
    - void* threadFunc(void* arg) {...; return NULL;}
    - pthread thread;
    - pthread_create(&thread, NULL, funcThread, (void*)inputArgs);
    - void* ret; pthread_join(thread, &ret);
    - pthread_detach(thread);

            ----
            1️⃣ Mutex
            Language	Type / Class	Functions / Methods	Ghi chú
            C	pthread_mutex_t	pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_trylock, pthread_mutex_unlock	Bảo vệ critical section
            C++	std::mutex	lock(), try_lock(), unlock()	C++11 trở lên, RAII với std::lock_guard<std::mutex>

            C++ RAII ví dụ:

            std::mutex mtx;
            {
                std::lock_guard<std::mutex> lock(mtx); // tự unlock khi ra scope
                // critical section
            }

            2️⃣ Condition Variable (CV)
            Language	Type / Class	Functions / Methods	Ghi chú
            C	pthread_cond_t	pthread_cond_init, pthread_cond_destroy, pthread_cond_wait, pthread_cond_signal, pthread_cond_broadcast	Wait + signal condition, kết hợp mutex
            C++	std::condition_variable	wait(lock), notify_one(), notify_all()	C++11 trở lên, kết hợp std::unique_lock<std::mutex>

            C++ example:

            std::condition_variable cv;
            std::mutex mtx;
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [](){ return ready; });

            3️⃣ Semaphore
            Language	Type / Class	Functions / Methods	Ghi chú
            C (POSIX)	sem_t	sem_init, sem_destroy, sem_wait, sem_trywait, sem_post, sem_getvalue	Counting hoặc binary semaphore
            C++	C++20: std::counting_semaphore<N>	acquire(), try_acquire(), release()	Trước C++20 phải dùng POSIX semaphore hoặc tự implement
            4️⃣ Spinlock
            Language	Type / Class	Functions / Methods	Ghi chú
            C	pthread_spinlock_t	pthread_spin_init, pthread_spin_destroy, pthread_spin_lock, pthread_spin_trylock, pthread_spin_unlock	Lock nhanh, không sleep
            C++	Không có chuẩn, có thể dùng atomic flag	std::atomic_flag test_and_set/clear	Thường dùng cho lock rất ngắn
            5️⃣ Read-Write Lock (RW-lock)
            Language	Type / Class	Functions / Methods	Ghi chú
            C	pthread_rwlock_t	pthread_rwlock_init, pthread_rwlock_destroy, pthread_rwlock_rdlock, pthread_rwlock_wrlock, pthread_rwlock_unlock	Cho phép nhiều reader, 1 writer
            C++	C++17: std::shared_mutex	lock_shared(), unlock_shared(), lock(), unlock()	Shared lock cho reader, exclusive lock cho writer
            6️⃣ Pipe (IPC)
            Language	Function / Method	Ghi chú
            C / C++	pipe(int fd[2]), read(fd[0], ...), write(fd[1], ...)	Dùng cho byte-stream, FIFO, giữa process hoặc thread
            7️⃣ Message Queue (POSIX MQ)
            Language	Function / Method	Ghi chú
            C / C++	mq_open(), mq_close(), mq_unlink(), mq_send(), mq_receive(), mq_getattr(), mq_setattr()	Thread hoặc process có thể gửi/nhận message
            8️⃣ Shared Memory
            Language	Function / Method	Ghi chú
            C / C++	shm_open(), ftruncate(), mmap(), munmap(), close(), shm_unlink()	Thread có thể trực tiếp truy cập memory, mutex/semaphore bảo vệ truy cập
            Tóm tắt cách chọn trong multithread C/C++
            Mục đích	C	C++
            Bảo vệ critical section	pthread_mutex_t	std::mutex + lock_guard
            Wait/notify	pthread_cond_t	std::condition_variable
            Counting resource	sem_t	std::counting_semaphore (C++20) hoặc POSIX
            Nhiều reader / 1 writer	pthread_rwlock_t	std::shared_mutex
            Lock nhanh	pthread_spinlock_t	atomic_flag

            Nếu bạn muốn, mình có thể vẽ sơ đồ “bản đồ IPC + thread primitive C/C++”: ai wait/block ai, semaphore/cv/mutex dùng khi nào, để nhìn trực quan toàn bộ.

            Bạn có muốn mình vẽ không?
            ----

cơ chế IPC, synchronization (mutex, semaphore).

Memory Layout

stack, heap, bss, data section – quan trọng cho secure design.

POSIX API
  POSIX định nghĩa tập các hàm, macro, và interface chuẩn cho:
    - Process management
    - Threading
    - File I/O
    - IPC (Inter-Process Communication)
    - Signals
    - Time, timers, và nhiều thứ khác

file I/O (open/read/write/close), socket cơ bản, pthread (pthread_create, mutex/condvar).

Real-time OS concept

task scheduling, priority, preemption (basic level).


-------------------------------------
3️⃣ Secure Coding & Secure Design

JD nhấn mạnh secure coding & security concept, bạn cần nắm:

Threat Modeling Basics
  Common model:
  1. STRIDE (Microsoft) – phân loại các loại đe dọa:
    - Spoofing: giả mạo danh tính
    - Tampering: sửa đổi dữ liệu
    - Repudiation: từ chối hành động
    - Information Disclosure: lộ dữ liệu
    - Denial of Service: từ chối dịch vụ
    - Elevation of Privilege: leo thang quyền
  2. PASTA (Process for Attack Simulation and Threat Analysis) – tập trung vào rủi ro và mô phỏng tấn công.
  Mitigation & Prioritization:
    Announce thread:
    - Impact (Tác động nếu xảy ra)
    - Likelihood (Khả năng xảy ra)
    plan migration:
    - Ví dụ: mã hóa dữ liệu, xác thực mạnh, kiểm soát truy cập.
    priority solve the most important thread first

Confidentiality, Integrity, Availability (CIA triad).
    - CIA Triad là bộ ba nguyên tắc cốt lõi để đánh giá mức độ bảo mật của một hệ thống thông tin. Nó định nghĩa những gì cần bảo vệ và tại sao cần bảo vệ.
    - CIA gồm:
      - Confidentiality (Bảo mật thông tin – bí mật)
        - EX: 
          - Mã hóa dữ liệu nhạy cảm (password, token, dữ liệu cá nhân)
          - Kiểm soát truy cập (Access control, Role-based access)
          - Sử dụng VPN, SSL/TLS để bảo vệ dữ liệu truyền qua mạng
        - Threat: Data breach, sniffing, unauthorized access, insider threat
      - Integrity (Toàn vẹn thông tin)
        - Ex:
          - Checksum hoặc hash (SHA-256) để phát hiện thay đổi dữ liệu
          - Digital signatures cho các giao dịch
          - Kiểm soát phiên bản (version control)
        - Threat:
          - Data tampering, man-in-the-middle attack, malware sửa file
      - Availability (Khả dụng thông tin)
        - Ex:
          - Redundancy (server dự phòng)
          - Backup định kỳ
          - Load balancing, DDoS mitigation
          - Hệ thống fault-tolerant
        - Threat:
          - DoS/DDoS attack, phần cứng hỏng, lỗi phần mềm, thiên tai
Attack surface reduction, secure boot concept.
  1. Attack Surface Reduction (Giảm bề mặt tấn công)
  Khái niệm
    - Attack surface là tổng thể các điểm trong hệ thống mà kẻ tấn công có thể khai thác để xâm nhập hoặc gây hại.
    - Attack Surface Reduction (ASR) là các biện pháp giảm số lượng điểm tấn công tiềm năng, làm hệ thống an toàn hơn.
    => Nói cách khác: “Nếu bạn càng ít cửa sổ mở cho kẻ xấu, thì kẻ xấu càng khó vào.”
  Các loại Attack Surface
    - Network attack surface – các dịch vụ mở trên mạng (HTTP, SSH, API endpoints…)
    - Software attack surface – chức năng, module hoặc library mà người dùng hoặc attacker có thể tương tác
    - User attack surface – người dùng hoặc người vận hành có thể bị lừa đảo (social engineering)
    - Physical attack surface – phần cứng bị truy cập trực tiếp (USB, cổng debug, console)
  Các biện pháp giảm Attack Surface
    - Loại bỏ các dịch vụ không cần thiết: tắt module hoặc port không dùng
    - Hạn chế quyền truy cập: Principle of Least Privilege (PoLP)
    - Cập nhật và vá lỗi: patch các library, OS, firmware
    - Kiểm soát input: validate và sanitize dữ liệu đầu vào
    - Network segmentation: chia mạng ra các vùng an toàn (DMZ, VLAN)
    -> Mục tiêu: giảm các “cửa sổ” mà kẻ tấn công có thể sử dụng.

  2. Secure Boot (Khởi động an toàn)
  Khái niệm
    Secure Boot là một cơ chế bảo mật phần mềm/firmware giúp chỉ cho phép chạy phần mềm/OS được ký hợp pháp trên thiết bị khi khởi động.
    Nói cách khác: “Thiết bị chỉ chạy những code được nhà sản xuất hoặc người quản lý tin tưởng.”
  Nguyên lý hoạt động
    Khi bật thiết bị, firmware (BIOS/UEFI) kiểm tra chữ ký số (digital signature) của bootloader.
    Nếu bootloader hợp lệ → hệ thống tiếp tục khởi động OS.
    Nếu bootloader không hợp lệ hoặc bị sửa đổi → thiết bị dừng khởi động hoặc chuyển sang chế độ recovery.
  Lợi ích của Secure Boot
    Ngăn chặn malware/bootkit chèn vào firmware hoặc OS
    Đảm bảo hệ thống khởi động chỉ chạy phần mềm tin cậy
    Là nền tảng cho các cơ chế bảo mật nâng cao khác (TPM, measured boot, device attestation)
  Ví dụ
    Trên PC/Server: UEFI Secure Boot đảm bảo chỉ chạy Windows/Linux kernel được ký
    Trên IoT/Embedded: Firmware update phải được ký trước khi flash vào thiết bị



Secure Coding Practices
  tránh buffer overflow, integer overflow/underflow.
  kiểm tra input, validate data range.
  tránh undefined behavior.

Cryptography Basics
  symmetric vs asymmetric crypto, hash, HMAC, key storage.
  HSM (Hardware Security Module) & TrustZone
  hiểu cơ bản về HSM: lưu trữ key an toàn, true random number generator.
  TrustZone / TEE (Trusted Execution Environment): tách code secure / non-secure.

-------------------------------------
4️⃣ CI/CD, DevOps, SAFe, Scrum

Không cần quá sâu, nhưng nên nắm:

CI/CD Pipeline
  build automation (Jenkins, GitLab CI).
  unit test, static analysis (MISRA C, Coverity).

Scrum/SAFe
  role (Scrum Master, Product Owner).
  sprint planning, review, retrospective.

-------------------------------------
5️⃣ Kỹ năng Phân Tích & Giải Bài Tập

Code challenge cho thấy họ quan tâm đến:

Thiết kế struct hợp lý

chia trường dữ liệu rõ ràng, dùng union nếu cần.

function pointer để xử lý polymorphism.

Xử lý endianess

convert từ mảng byte → kiểu dữ liệu đúng.

Counting & grouping

dùng map hoặc unordered_map để đếm sensor có cùng raw value.

Viết Class C++ chuẩn

rule of 5 (constructor, copy/move constructor, destructor).

dynamic memory management.

-------------------------------------
6️⃣ Bài Tập Ôn Luyện

Mình gợi ý một số bài bạn có thể tự luyện:

Parse raw sensor data từ uint8_t buffer[4] → int/float → xử lý theo công thức → in ra kết quả.

Viết MyVector

push_back, pop_back, resize (tự tăng capacity).

template hóa MyVector cho generic type.

Viết function pointer dispatch

ví dụ: array các sensor, gọi process thông qua function pointer.

Thread Safety

tạo 2 thread: 1 thread push data vào MyVector, 1 thread pop → dùng mutex bảo vệ.

Viết CI/CD-like script

ví dụ viết Python script build + run unit test tự động.

7️⃣ Ôn Tiếng Anh Giao Tiếp

Vì môi trường quốc tế, bạn nên luyện cách giải thích giải pháp rõ ràng bằng tiếng Anh:

“I used a struct with a function pointer to achieve polymorphism in C.”

“I considered endianess when converting raw bytes into sensor data.”

“To ensure security, I would validate input data and check for overflow.”