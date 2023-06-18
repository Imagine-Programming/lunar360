#pragma once 

#include <windows.h>
#include <xinput.h>

#include <format>
#include <cmath>
#include <unordered_map>
#include <optional>
#include <stdexcept>
#include <functional>

#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "Xinput9_1_0.lib")

struct xbox_thumb_delta {
	double x; // X-direction
	double y; // Y-direction
	double m; // magnitute
	double n; // normalized magnitute
};

class xbox_controller_button {
public:
	xbox_controller_button(WORD button) noexcept
		: button_(button), in_double_click_(false), down_(false), last_down_time_(std::chrono::steady_clock::now()) {}

	void poll(const XINPUT_STATE& state) {
		auto down_now = (state.Gamepad.wButtons & button_) != 0; 
		
		if (!down_ && down_now) {
			// mouse-down
			down_ = true;

			if (on_down_) on_down_(down_userdata_);
			
			if (in_double_click_) {
				in_double_click_ = false;

				// measure time 
				auto now = std::chrono::steady_clock::now();
				auto delta = now - last_down_time_;
				
				// see if delta is below double_click_threshold_
				if (delta < double_click_threshold_) {
					// double-click
					if (on_double_) on_double_(double_userdata_);
				}

				return;
			}

			in_double_click_ = true;
			last_down_time_ = std::chrono::steady_clock::now(); 
		} else if (down_ && !down_now) {
			// mouse-up
			down_ = false;
			if (on_up_) on_up_(up_userdata_);
		}

		if (in_double_click_) {
			auto now = std::chrono::steady_clock::now();
			auto delta = now - last_down_time_;
			
			if (delta > double_click_threshold_) {
				in_double_click_ = false;
				if (on_single_) on_single_(single_userdata_);
			}
		}
	}

	void set_down_handler  (std::function<void(void* udata)> f, void* udata) { on_down_   = f; down_userdata_   = udata; }
	void set_up_handler    (std::function<void(void* udata)> f, void* udata) { on_up_     = f; up_userdata_     = udata; }
	void set_single_handler(std::function<void(void* udata)> f, void* udata) { on_single_ = f; single_userdata_ = udata; }
	void set_double_handler(std::function<void(void* udata)> f, void* udata) { on_double_ = f; double_userdata_ = udata; }

	void* get_down_userdata()   { return down_userdata_; }
	void* get_up_userdata()     { return up_userdata_; }
	void* get_single_userdata() { return single_userdata_; }
	void* get_double_userdata() { return double_userdata_; }

	void set_down_userdata  (void* udata) { down_userdata_ = udata; }
	void set_up_userdata    (void* udata) { up_userdata_ = udata; }
	void set_single_userdata(void* udata) { single_userdata_ = udata; }
	void set_double_userdata(void* udata) { double_userdata_ = udata; }
private:
	WORD button_;

	// last down time using chrono:
	bool in_double_click_;
	bool down_;
	std::chrono::time_point<std::chrono::steady_clock> last_down_time_;
	
	std::function<void(void* udata)> on_down_ = nullptr;
	void* down_userdata_ = nullptr;
	std::function<void(void* udata)> on_up_ = nullptr;
	void* up_userdata_ = nullptr;
	std::function<void(void* udata)> on_single_ = nullptr;
	void* single_userdata_ = nullptr;
	std::function<void(void* udata)> on_double_ = nullptr;
	void* double_userdata_ = nullptr;

	const std::chrono::milliseconds double_click_threshold_ = std::chrono::milliseconds(GetDoubleClickTime());
};

class xbox_controller {
public:
	xbox_controller(DWORD id)
		: controller_index_(id), connected_(false), changed_(false)
		, state_(init<XINPUT_STATE>()), previous_state_(init<XINPUT_STATE>()) 
	{
		add_button_handlers();
	}

	xbox_controller(DWORD id, const XINPUT_STATE& state)
		: controller_index_(id), connected_(false), changed_(false)
		, state_(state), previous_state_(init<XINPUT_STATE>()) 
	{
		add_button_handlers();
		connected_ = true; 
	}

	void add_button_handlers() {
		buttons_.try_emplace(XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_A);
		buttons_.try_emplace(XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_B); 
		buttons_.try_emplace(XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_X); 
		buttons_.try_emplace(XINPUT_GAMEPAD_Y, XINPUT_GAMEPAD_Y); 

		buttons_.try_emplace(XINPUT_GAMEPAD_DPAD_UP, XINPUT_GAMEPAD_DPAD_UP); 
		buttons_.try_emplace(XINPUT_GAMEPAD_DPAD_DOWN, XINPUT_GAMEPAD_DPAD_DOWN); 
		buttons_.try_emplace(XINPUT_GAMEPAD_DPAD_LEFT, XINPUT_GAMEPAD_DPAD_LEFT); 
		buttons_.try_emplace(XINPUT_GAMEPAD_DPAD_RIGHT, XINPUT_GAMEPAD_DPAD_RIGHT); 

		buttons_.try_emplace(XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_LEFT_SHOULDER); 
		buttons_.try_emplace(XINPUT_GAMEPAD_RIGHT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER); 
		
		buttons_.try_emplace(XINPUT_GAMEPAD_LEFT_THUMB, XINPUT_GAMEPAD_LEFT_THUMB); 
		buttons_.try_emplace(XINPUT_GAMEPAD_RIGHT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB); 

		buttons_.try_emplace(XINPUT_GAMEPAD_START, XINPUT_GAMEPAD_START); 
		buttons_.try_emplace(XINPUT_GAMEPAD_BACK, XINPUT_GAMEPAD_BACK);
	}
	
	void on_button_down(WORD button, std::function<void(void*)> f, void* udata) {
		if (buttons_.contains(button)) 
			buttons_.at(button).set_down_handler(f, udata); 
	}

	void* get_button_down_userdata(WORD button) {
		if (buttons_.contains(button))
			return buttons_.at(button).get_down_userdata(); 
		return nullptr;
	}

	void set_button_down_userdata(WORD button, void* udata) {
		if (buttons_.contains(button))
			buttons_.at(button).set_down_userdata(udata); 
	}

	void on_button_up(WORD button, std::function<void(void*)> f, void* udata) {
		if (buttons_.contains(button))
			buttons_.at(button).set_up_handler(f, udata);
	}

	void* get_button_up_userdata(WORD button) {
		if (buttons_.contains(button))
			return buttons_.at(button).get_up_userdata();
		return nullptr;
	}

	void set_button_up_userdata(WORD button, void* udata) {
		if (buttons_.contains(button))
			buttons_.at(button).set_up_userdata(udata);
	}

	void on_button_single(WORD button, std::function<void(void*)> f, void* udata) {
		if (buttons_.contains(button))
			buttons_.at(button).set_single_handler(f, udata);
	}

	void* get_button_single_userdata(WORD button) {
		if (buttons_.contains(button))
			return buttons_.at(button).get_single_userdata();
		return nullptr;
	}

	void set_button_single_userdata(WORD button, void* udata) {
		if (buttons_.contains(button))
			buttons_.at(button).set_single_userdata(udata);
	}

	void on_button_double(WORD button, std::function<void(void*)> f, void* udata) {
		if (buttons_.contains(button))
			buttons_.at(button).set_double_handler(f, udata);
	}

	void* get_button_double_userdata(WORD button) {
		if (buttons_.contains(button))
			return buttons_.at(button).get_double_userdata();
		return nullptr;
	}

	void set_button_double_userdata(WORD button, void* udata) {
		if (buttons_.contains(button))
			buttons_.at(button).set_double_userdata(udata);
	}

	void visit_button_userdata(std::function<void(WORD, void*, void*, void*, void*)> f) {
		for (auto& [button, xbox_button] : buttons_) 
			f(button, xbox_button.get_down_userdata(), xbox_button.get_up_userdata(), xbox_button.get_single_userdata(), xbox_button.get_double_userdata());
	}

	void set_left_thumb_deadzone(SHORT deadzone) noexcept {
		left_thumb_deadzone_ = deadzone;
	}

	SHORT left_thumb_deadzone() const noexcept {
		return left_thumb_deadzone_;
	}

	void set_right_thumb_deadzone(SHORT deadzone) noexcept {
		right_thumb_deadzone_ = deadzone;
	}

	SHORT right_thumb_deadzone() const noexcept {
		return right_thumb_deadzone_;
	}

	void set_trigger_threshold(SHORT threshold) noexcept {
		trigger_threshold_ = threshold;
	}

	SHORT trigger_threshold() const noexcept {
		return trigger_threshold_;
	}

	std::optional<XINPUT_CAPABILITIES> capabilities() const noexcept {
		auto caps = init<XINPUT_CAPABILITIES>();

		if (XInputGetCapabilities(controller_index_, XINPUT_FLAG_GAMEPAD, &caps) == ERROR_SUCCESS) 
			return caps;
		
		return {};
	}

	bool connected() const noexcept {
		return connected_;
	}

	bool changed() const noexcept {
		return changed_;
	}

	const XINPUT_STATE& state() const noexcept {
		return state_;
	}

	const XINPUT_STATE& previous_state() const noexcept {
		return previous_state_;
	}

	void poll() {
		auto state = init<XINPUT_STATE>();
		auto result = XInputGetState(controller_index_, &state);

		if (result == ERROR_SUCCESS) {
			// controller is connected
			connected_ = true;
			// update the state
			previous_state_ = state_;
			state_ = state;
			changed_ = (state_.dwPacketNumber != previous_state_.dwPacketNumber);

			// poll the buttons
			for (auto& [button, xbox_button] : buttons_) 
				xbox_button.poll(state_); 
		}
		else {
			// controller is not connected
			connected_ = false;
		}
	}

	double left_trigger_delta() const noexcept {
		return get_trigger_delta(state_.Gamepad.bLeftTrigger);
	}

	double right_trigger_delta() const noexcept {
		return get_trigger_delta(state_.Gamepad.bRightTrigger);
	}

	bool left_trigger_toggled() const noexcept {
		// if the trigger is pressed, and it wasn't pressed before or the other way around
		return (state_.Gamepad.bLeftTrigger > trigger_threshold_) != (previous_state_.Gamepad.bLeftTrigger > trigger_threshold_);
	}

	bool right_trigger_toggled() const noexcept {
		// if the trigger is pressed, and it wasn't pressed before or the other way around
		return (state_.Gamepad.bRightTrigger > trigger_threshold_) != (previous_state_.Gamepad.bRightTrigger > trigger_threshold_);
	}

	xbox_thumb_delta left_thumb_delta() const noexcept {
		return get_thumb_delta(state_.Gamepad.sThumbLX, state_.Gamepad.sThumbLY, left_thumb_deadzone_, MAXSHORT);
	}

	xbox_thumb_delta right_thumb_delta() const noexcept {
		return get_thumb_delta(state_.Gamepad.sThumbRX, state_.Gamepad.sThumbRY, right_thumb_deadzone_, MAXSHORT);
	}

	static std::optional<DWORD> get_first_active_controller_index() {
		for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) { 
			auto state = init<XINPUT_STATE>(); 
			auto result = XInputGetState(i, &state);
			if (result == ERROR_SUCCESS) 
				return i;
		}

		return {};
	}

	static std::optional<xbox_controller> get_first_active_controller() {
		DWORD dwResult;

		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
			auto state = init<XINPUT_STATE>();
			dwResult = XInputGetState(i, &state);
			if (dwResult == ERROR_SUCCESS)
				return xbox_controller(i, state);
		}

		return {};
	}
private:
	DWORD controller_index_;

	bool connected_;
	bool changed_;

	XINPUT_STATE state_;
	XINPUT_STATE previous_state_;

	SHORT left_thumb_deadzone_ = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	SHORT right_thumb_deadzone_ = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	SHORT trigger_threshold_ = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

	std::unordered_map<WORD, xbox_controller_button> buttons_ = {};

	template <typename T>
	static inline constexpr T init() noexcept {
		T v = { 0 };
		ZeroMemory(&v, sizeof(T));
		return v;
	}

	double get_trigger_delta(BYTE trigger) const noexcept {
		if (trigger < trigger_threshold_) {
			return 0.0;
		}
		else {
			return (trigger - trigger_threshold_) / (255.0 - trigger_threshold_);
		}
	}

	static xbox_thumb_delta get_thumb_delta(SHORT x, SHORT y, SHORT deadzone, SHORT max) {
		auto LX = static_cast<double>(x);
		auto LY = static_cast<double>(y);

		//determine how far the controller is pushed
		auto magnitude = sqrt(LX * LX + LY * LY);

		//determine the direction the controller is pushed
		auto normalizedLX = LX / magnitude;
		auto normalizedLY = LY / magnitude;

		auto normalizedMagnitude = 0.0;

		//check if the controller is outside a circular dead zone
		if (magnitude > static_cast<double>(deadzone))
		{
			//clip the magnitude at its expected maximum value
			if (magnitude > static_cast<double>(max)) magnitude = static_cast<double>(max);

			//adjust magnitude relative to the end of the dead zone
			magnitude -= static_cast<double>(deadzone);

			//optionally normalize the magnitude with respect to its expected range
			//giving a magnitude value of 0.0 to 1.0
			normalizedMagnitude = magnitude / (static_cast<double>(max) - static_cast<double>(deadzone));
		}
		else //if the controller is in the deadzone zero out the magnitude
		{
			magnitude = 0.0;
			normalizedMagnitude = 0.0;
		}

		return { normalizedLX, normalizedLY * -1.0, magnitude, normalizedMagnitude };
	}
};