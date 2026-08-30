/**
 * audioManager.js
 * Quản lý tất cả audio assets của game
 * 
 * Trách nhiệm riêng biệt:
 * - Load và play audio files
 * - Quản lý tất cả sound effects
 * - Không can thiệp vào logic game
 */

class AudioManager {
    constructor() {
        this.sounds = {};
        this.init();
    }

    /**
     * Khởi tạo và load tất cả audio assets
     * Base path: ../assets/audio/
     */
    init() {
        // Định nghĩa tất cả sound assets
        const audioAssets = {
            wrong: '../assets/audio/wrong.wav',      // Wrong answer
            right: '../assets/audio/right.wav',      // Correct answer
            nextQuestion: '../assets/audio/moun.wav', // Move to next question
            finalRound: '../assets/audio/final_round.wav' // Finish game
        };

        // Load tất cả audio files
        for (const [key, path] of Object.entries(audioAssets)) {
            const audio = new Audio(path);
            audio.preload = 'auto';
            this.sounds[key] = audio;
        }

        console.log('AudioManager đã khởi tạo');
    }

    /**
     * Play sound khi trả lời sai
     */
    playWrong() {
        this.playSound('wrong');
    }

    /**
     * Play sound khi trả lời đúng
     */
    playCorrect() {
        this.playSound('right');
    }

    /**
     * Play sound khi chuyển sang câu tiếp theo
     */
    playNextQuestion() {
        this.playSound('nextQuestion');
    }

    /**
     * Play sound khi kết thúc game
     */
    playFinalRound() {
        this.playSound('finalRound');
    }

    /**
     * Play sound (internal method)
     * @param {string} key - Tên sound cần play
     */
    playSound(key) {
        if (this.sounds[key]) {
            // Reset audio về đầu để có thể play liên tiếp
            this.sounds[key].currentTime = 0;
            // Play
            this.sounds[key].play().catch(error => {
                console.warn(`Không thể play ${key}:`, error);
            });
        } else {
            console.warn(`Sound không tồn tại: ${key}`);
        }
    }
}

// Khởi tạo audioManager khi cần (được gọi trong main.js)
let audioManager = null;
