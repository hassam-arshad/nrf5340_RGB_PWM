/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM-based RGB LED control
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

static const struct pwm_dt_spec red_pwm_led =
	PWM_DT_SPEC_GET(DT_ALIAS(red_pwm_led));
static const struct pwm_dt_spec green_pwm_led =
	PWM_DT_SPEC_GET(DT_ALIAS(green_pwm_led));
static const struct pwm_dt_spec blue_pwm_led =
	PWM_DT_SPEC_GET(DT_ALIAS(blue_pwm_led));

#define STEP_SIZE PWM_USEC(2000)

void set_rgb_color(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t pulse_red, pulse_green, pulse_blue; /* pulse widths */
    int ret;
	red = 0.7 * red;	//compensating red color due to red more prominent during testing
    // No need to check PWM readiness here
    pulse_red = red * (red_pwm_led.period + 1) / 255;
    pulse_green = green * (green_pwm_led.period + 1) / 255;
    pulse_blue = blue * (blue_pwm_led.period + 1) / 255;

    ret = pwm_set_pulse_dt(&red_pwm_led, pulse_red);
    if (ret != 0) {
        printk("Error %d: red write failed\n", ret);
        return;
    }

    ret = pwm_set_pulse_dt(&green_pwm_led, pulse_green);
    if (ret != 0) {
        printk("Error %d: green write failed\n", ret);
        return;
    }

    ret = pwm_set_pulse_dt(&blue_pwm_led, pulse_blue);
    if (ret != 0) {
        printk("Error %d: blue write failed\n", ret);
        return;
    }

    // Calculate the complementary pulse width for inverted polarity
 /*   pulse_red = (255 - red) * (red_pwm_led.period + 1) / 255;
    pulse_green = (255 - green) * (green_pwm_led.period + 1) / 255;
    pulse_blue = (255 - blue) * (blue_pwm_led.period + 1) / 255;

    ret = pwm_set_pulse_dt(&red_pwm_led, pulse_red);
    if (ret != 0) {
        printk("Error %d: red write failed\n", ret);
        return;
    }

    ret = pwm_set_pulse_dt(&green_pwm_led, pulse_green);
    if (ret != 0) {
        printk("Error %d: green write failed\n", ret);
        return;
    }

    ret = pwm_set_pulse_dt(&blue_pwm_led, pulse_blue);
    if (ret != 0) {
        printk("Error %d: blue write failed\n", ret);
        return;
    }*/
}

void set_rgb_red()
{
	//    {0xFF1AE5, {255, 0, 0} }, // Red
	set_rgb_color(255, 0, 0);
}

void set_rgb_red_2()
{
	//  {0xFF2AD5, {255, 63, 0} }, // Red-Orange (Red 2)
	set_rgb_color(255, 63, 0);
}
void set_rgb_red_3()
{
	//  {0xFF0AF5, {255, 127, 0} }, // Orange (Red 3)
	set_rgb_color(255, 127, 0);
}
void set_rgb_red_4()
{
	//   {0xFF38C7, {255, 191, 0} }, // Yellow-Orange (Red 4)
	set_rgb_color(255, 191, 0);
}

void set_rgb_red_5()
{
	//    {0xFF18E7, {255, 255, 0} }, // Yellow (Red 5)
	set_rgb_color(255, 255, 0);
}
void set_rgb_green()
{
	//  {0xFF9A65, {0, 255, 0} }, // Green
	set_rgb_color(0, 255, 0);
}
void set_rgb_green_2()
{
	//    {0xFFAA55, {0, 255, 63} }, // Green-Aqua (Green 2)
	set_rgb_color(0, 255, 63);
}
void set_rgb_green_3()
{
	//  {0xFF8A75, {0, 255, 127} }, // Aqua (Green 3)
	set_rgb_color(0, 255, 127);
}
void set_rgb_green_4()
{
	//  {0xFFB847, {0, 255, 191} }, // Aqua-Cyan (Green 4)
	set_rgb_color(0, 255, 191);
}
void set_rgb_green_5()
{
	//   {0xFF9867, {0, 255, 255} }, // Cyan (Green 5)
	set_rgb_color(0, 255, 255);
}
void set_rgb_blue()
{
	//  {0xFFA25D, {0, 0, 255} }, // Blue
	set_rgb_color(0, 0, 255);
}

void set_rgb_blue_2()
{
	//    {0xFF926D, {63, 0, 255} }, // Blue-Purple (Blue 2)
	set_rgb_color(63, 0, 255);
}
void set_rgb_blue_3()
{
	//    {0xFFB24D, {127, 0, 255} }, // Purple (Blue 3)
	set_rgb_color(127, 0, 255);
}
void set_rgb_blue_4()
{
	//  {0xFF7887, {191, 0, 255} }, // Purple-Magenta (Blue 4)
	set_rgb_color(191, 0, 255);
}
void set_rgb_blue_5()
{
	//  {0xFF58A7, {255, 0, 255} }, // Magenta (Blue 5)
	set_rgb_color(255, 0, 255);
}
void set_rgb_white()
{
	//  {0xFF22DD, {255, 255, 255} }, // White

	set_rgb_color(255, 255, 255);
}
void set_rgb_white_2()
{
	//  {0xFF12ED, {255, 191, 191} }, // White 2
	set_rgb_color(255, 191, 191);
}
void set_rgb_white_3()
{
	//  {0xFFF807, {191, 191, 255} }, // White 4
	set_rgb_color(191, 191, 255);
}

int main(void)
{
	// uint32_t pulse_red, pulse_green, pulse_blue; /* pulse widths */
	// int ret;

	printk("PWM-based RGB LED control\n");

	if (!device_is_ready(red_pwm_led.dev) ||
	    !device_is_ready(green_pwm_led.dev) ||
	    !device_is_ready(blue_pwm_led.dev)) {
		printk("Error: one or more PWM devices not ready\n");
		return 0;
	}

	while (1) {
/*
		for (pulse_red = 0U; pulse_red <= red_pwm_led.period;
		     pulse_red += STEP_SIZE) {
			ret = pwm_set_pulse_dt(&red_pwm_led, pulse_red);
			if (ret != 0) {
				printk("Error %d: red write failed\n", ret);
				return 0;
			}

			for (pulse_green = 0U;
			     pulse_green <= green_pwm_led.period;
			     pulse_green += STEP_SIZE) {
				ret = pwm_set_pulse_dt(&green_pwm_led,
						       pulse_green);
				if (ret != 0) {
					printk("Error %d: green write failed\n",
					       ret);
					return 0;
				}

				for (pulse_blue = 0U;
				     pulse_blue <= blue_pwm_led.period;
				     pulse_blue += STEP_SIZE) {
					ret = pwm_set_pulse_dt(&blue_pwm_led,
							       pulse_blue);
					if (ret != 0) {
						printk("Error %d: "
						       "blue write failed\n",
						       ret);
						return 0;
					}
					k_sleep(K_SECONDS(1));
				}
			}
		}
	*/
// 	ret = pwm_set_pulse_dt(&red_pwm_led, PWM_MSEC(5));
// 	ret = pwm_set_pulse_dt(&green_pwm_led, PWM_MSEC(5));
// 	ret = pwm_set_pulse_dt(&blue_pwm_led, PWM_MSEC(10));

// k_sleep(K_SECONDS(5));
// 	ret = pwm_set_pulse_dt(&red_pwm_led, PWM_MSEC(4));
// 	ret = pwm_set_pulse_dt(&green_pwm_led, PWM_MSEC(4));
// 	ret = pwm_set_pulse_dt(&blue_pwm_led, PWM_MSEC(4));

// k_sleep(K_SECONDS(5));

// 	ret = pwm_set_pulse_dt(&red_pwm_led, PWM_MSEC(1));
// 	ret = pwm_set_pulse_dt(&green_pwm_led, PWM_MSEC(1));
// 	ret = pwm_set_pulse_dt(&blue_pwm_led, PWM_MSEC(5));

// 	k_sleep(K_SECONDS(5));
// 	ret = pwm_set_pulse_dt(&red_pwm_led, PWM_MSEC(5));
// 	ret = pwm_set_pulse_dt(&green_pwm_led, PWM_MSEC(5));
// 	ret = pwm_set_pulse_dt(&blue_pwm_led, PWM_MSEC(5));

// Example: Set RGB color to red
        set_rgb_color(255, 0, 0);
        k_sleep(K_SECONDS(1));

        // Example: Set RGB color to green
        set_rgb_color(0, 255, 0);
        k_sleep(K_SECONDS(1));

        // Example: Set RGB color to blue
        set_rgb_color(0, 0, 255);
        k_sleep(K_SECONDS(1));

        // Add more color settings as needed

		set_rgb_color(200, 165, 0);	//orange
        k_sleep(K_SECONDS(5));

		set_rgb_color(0, 0, 0);
        k_sleep(K_SECONDS(5));

		set_rgb_color(255, 255, 0);
        k_sleep(K_SECONDS(5));

		set_rgb_color(255, 0, 255);
        k_sleep(K_SECONDS(5));

		set_rgb_color(0, 255, 255);
        k_sleep(K_SECONDS(5));


	}
	return 0;
}
