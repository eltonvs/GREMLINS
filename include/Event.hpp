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
     * @param _t A time-stamp
     */
    Event(void *_p, std::time_t _t) {
        m_ptr = _p;
        m_time = _t;
    }

    /**
     * @brief Gets the Event time-stamp
     * @return The time-stamp
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

    /**
     * @brief Overloads the < operator
     * @param _e The another event to be comparised
     * @return True or False, comparing by the time-stamp
     */
    bool operator<(const Event &_e) const {
        return m_time < _e.m_time;
    }

 private:
    void *m_ptr;         //!< The Event pointer
    std::time_t m_time;  //!< The Event time-stamp
};
