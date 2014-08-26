/*
 * Copyright 2013 Francisco Franco
 * Copyright 2014 savoca <adeddo27@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include "../../sound/soc/codecs/wcd9xxx-common.h"

#define SOUNDCONTROL_VERSION 0

extern int high_perf_mode;

static ssize_t hph_perf_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	size_t count = 0;

	count += sprintf(buf, "%d\n", high_perf_mode);

	return count;
}

static ssize_t hph_perf_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	if (buf[0] >= '0' && buf[0] <= '1' && buf[1] == '\n')
		if (high_perf_mode != buf[0] - '0')
			high_perf_mode = buf[0] - '0';

	return count;
}

static ssize_t soundcontrol_version(struct device * dev, struct device_attribute * attr, char * buf)
{
    return sprintf(buf, "%d\n", SOUNDCONTROL_VERSION);
}

static DEVICE_ATTR(highperf_enabled, 0664, hph_perf_show, hph_perf_store);
static DEVICE_ATTR(version, 0664 , soundcontrol_version, NULL);

static struct attribute *soundcontrol_attributes[] = 
{
	&dev_attr_highperf_enabled.attr,
	&dev_attr_version.attr,
	NULL
};

static struct attribute_group soundcontrol_group = 
{
	.attrs  = soundcontrol_attributes,
};

static struct miscdevice soundcontrol_device = 
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = "soundcontrol",
};

static int __init soundcontrol_init(void)
{
    int ret;

    pr_info("%s misc_register(%s)\n", __FUNCTION__, soundcontrol_device.name);

    ret = misc_register(&soundcontrol_device);

    if (ret) {
	    pr_err("%s misc_register(%s) fail\n", __FUNCTION__, soundcontrol_device.name);
	    return 1;
	}

    if (sysfs_create_group(&soundcontrol_device.this_device->kobj, &soundcontrol_group) < 0) {
	    pr_err("%s sysfs_create_group fail\n", __FUNCTION__);
	    pr_err("Failed to create sysfs group for device (%s)!\n", soundcontrol_device.name);
	}

    return 0;
}
late_initcall(soundcontrol_init);
