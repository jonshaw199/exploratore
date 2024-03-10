#ifndef EVENT_LISTENER_H_
#define EVENT_LISTENER_H_

class EventListener {
public:
  virtual void handle_event(int event);
};

#endif // EVENT_LISTENER_H_
