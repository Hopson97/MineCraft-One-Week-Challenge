#ifndef NON_MOVE
#define NON_MOVE

/// @brief Class that identifies entities not designed for physical movement.
class NonMovable {
  public:
    NonMovable(NonMovable &&) = delete;

    NonMovable &operator=(NonMovable &&) = delete;

  protected:
    NonMovable() = default;
};

#endif // NON_MOVE
