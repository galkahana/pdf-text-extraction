#pragma once

enum EResult {
   EResultOk,
   EResultErr,
};

template<typename T>
class Result {
    public:
        Result(); // ok
        Result(T inValue); // err

        bool IsOK();
        bool IsErr();

        T& GetValue();

        T GetValueOrDefault(T inDefaultValue);

    private:
        T value;
        EResult status;
};

template <typename T>
Result<T>::Result() {
    // use for bad result
    status = EResultErr;
}

template <typename T>
Result<T>::Result(T inValue) {
    // use for good result
    status = EResultOk;
    value = inValue;
}

template <typename T>
bool Result<T>::IsOK() {
    return EResultOk == status;
}

template <typename T>
bool Result<T>::IsErr() {
    return EResultErr == status;
}

template <typename T>
T& Result<T>::GetValue() {
    return value;
}

template <typename T>
T Result<T>::GetValueOrDefault(T inDefaultValue) {
    return EResultOk == status ? value : inDefaultValue;
}
