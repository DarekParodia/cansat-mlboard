#pragma once

/**
 * @brief System functions
 *
 * This namespace contains functions used for interaction with non-user codespace.
 * It has functions used for updating modules, calling their loops etc.
 */
namespace core {
    /**
     * @brief DO NOT USE!!
     *
     * This function is run only by main.cpp, it should be avoided anywhere else
     * it contains initialization code
     */
    void init();

    /**
     * @brief DO NOT USE!!
     *
     * This function is run only by main.cpp, it should be avoided anywhere else
     * it contains loop code
     */
    void loop();
} // namespace core
