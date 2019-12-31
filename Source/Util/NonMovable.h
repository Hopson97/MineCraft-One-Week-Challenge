#ifndef NON_MOVE
#define NON_MOVE

class NonMovable {
  public:
    NonMovable(NonMovable &&) = delete;

    NonMovable &operator=(NonMovable &&) = delete;

  protected:
    NonMovable() = default;
};

#endif // NON_MOVE
