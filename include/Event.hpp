/*!
 *  @file Event.hpp
 *  @brief Event Class Prototype
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the Event Class prototype
 */

class Event {
 public:
    /**
     * @brief Event default (empty) constructor
     */
    Event() {}

    /**
     * @brief Event Attibution constructor
     * @param _p A pointer
     * @param _t A time stamp
     */
    Event(void *_p, std::time_t _t) {
        m_ptr = _p;
        m_time = _t;
    }

    /**
     * @brief Gets the Event time stamp
     * @return The time stamp
     */
    std::time_t getTimeStamp() {
        return m_time;
    }

    /**
     * @brief Gets the pointer
     * @return The pointer
     */
    void *getMemoryPtr() {
        return m_ptr;
    }

 private:
    void *m_ptr;         //!< The Event pointer
    std::time_t m_time;  //!< The Event time stamp
};
