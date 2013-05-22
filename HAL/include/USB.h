/**
 * @file USB.h
 * @author Ashok Fernandez <azf10@uclive.ac.nz>
 * @date 16-04-2013
 * @breif USB API for HoustonOS Hardware Abstraction Layer (HAL)
 * 
 * Defines the public interface for the Hardware Abstraction Layer (HAL) for HoustonOS. The functions described
 * should be impleneted seperatly for each physical platform that the software is running on and compiled to a 
 * static library. This allows the same public interface to be be linked in to different implementations at compile
 * time, ensuring the code is portable across different physical platforms 
 */


typedef (char *) USB_message_t;

/**
 * @name    Init
 * @ingroup USB
 * @brief   Initialises the USB hardware and enumerates the hardware with the USB host device
 *
 * @param [void]
 *
 * @retval 1   USB initialised sucessfully
 * @retval 0  An error occured when initialising the USB
 *
 * Example Usage:
 * @code
 *    USB_init() // Initialise the USB hardware and enumerates the device
 * @endcode
 */
int USB_init(void);
