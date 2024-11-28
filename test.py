import hik_driver_py

cam = hik_driver_py.utils.init_SDK()

hik_driver_py.utils.set_trigger_mode_On(cam)
hik_driver_py.utils.set_trigger_source(cam, "Action1")
hik_driver_py.utils.set_action_keys(cam)
hik_driver_py.utils.start_grabbing(cam)

hik_driver_py.utils.issue_action_command(cam)

image_frame = hik_driver_py.utils.pop_image_buffer(cam)

hik_driver_py.utils.save_non_raw_image(1,image_frame,cam)

hik_driver_py.utils.close_device(cam)