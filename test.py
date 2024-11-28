import hik_driver

cam = hik_driver.utils.init_SDK()

hik_driver.utils.set_trigger_mode_On(cam)
hik_driver.utils.set_trigger_source(cam, "Action1")
hik_driver.utils.set_action_keys(cam)
hik_driver.utils.start_grabbing(cam)

hik_driver.utils.issue_action_command(cam)

image_frame = hik_driver.utils.pop_image_buffer(cam)

hik_driver.utils.save_non_raw_image(1,image_frame,cam)

hik_driver.utils.close_device(cam)