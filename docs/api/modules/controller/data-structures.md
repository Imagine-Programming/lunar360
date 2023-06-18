# Data Structures in lunar360.controller

## `xbox_thumb_delta`

A table describing the thumb delta, returned by functions like [controller_object:get_right_thumb_delta](api/modules/controller/get_right_thumb_delta.md).

### Fields

| Field | Type   | Description                            |
| ----- | ------ | -------------------------------------- |
| `x`   | number | The X delta.                           |
| `y`   | number | The Y delta.                           |
| `m`   | number | The magnitude of the delta.            |
| `n`   | number | The normalized magnitude of the delta. |

## `xinput_gamepad`

A table describing the XInput gamepad, returned as part of state by functions like [controller_object:get_state](api/modules/controller/get_state.md).

### Fields

| Field | Type    | Description                                      |
| ----- | ------- | ------------------------------------------------ |
| `wButtons`      | integer | The button bitmask.                    |
| `bLeftTrigger`  | integer | The left trigger value.                |
| `bRightTrigger` | integer | The right trigger value.               |
| `sThumbLX`      | integer | The left thumb X value.                |
| `sThumbLY`      | integer | The left thumb Y value.                |
| `sThumbRX`      | integer | The right thumb X value.               |
| `sThumbRY`      | integer | The right thumb Y value.               |

## `xinput_state`

A table describing the XInput state, returned by functions like [controller_object:get_state](api/modules/controller/get_state.md).

### Fields

| Field | Type     | Description                                     |
| ----- | -------- | ----------------------------------------------- |
| `dwPacketNumber` | integer | The packet number.                    |
| `gamepad`        | [xinput_gamepad](#xinput_gamepad) | The gamepad.|

## `xinput_vibration`

A table describing the XInput vibration, returned by functions like [controller_object:get_capabilities](api/modules/controller/get_capabilities.md).

### Fields

| Field | Type       | Description                                         |
| ----- | ---------- | --------------------------------------------------- |
| `wLeftMotorSpeed`  | integer | The left motor speed.                     |
| `wRightMotorSpeed` | integer | The right motor speed.                    |

## `xinput_capabilities`

A table describing the XInput capabilities, returned by functions like [controller_object:get_capabilities](api/modules/controller/get_capabilities.md).

### Fields

| Field       | Type                                  | Description             |
| ----------- | ------------------------------------- | ----------------------- |
| `Type`      | integer                               | The controller type.    |
| `SubType`   | integer                               | The controller subtype. |
| `Flags`     | integer                               | The controller flags.   |
| `Gamepad`   | [xinput_gamepad](#xinput_gamepad)     | The gamepad.            |
| `Vibration` | [xinput_vibration](#xinput_vibration) | The vibration.          |

