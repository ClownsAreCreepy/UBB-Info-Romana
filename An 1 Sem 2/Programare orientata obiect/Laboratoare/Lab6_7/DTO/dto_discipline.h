#pragma once
#include <string>
#include <utility>

using std::string;
using std::move;

/**
 * Clasa care tine evidenta frecventelor unei chestii din repository
 */
class ReportDTO final {
private:
    int count = 0;

public:
    /**
     * Constructor explicit pentru declararea initializata
     * @param count frecventa acelui tip
     */
    explicit ReportDTO(int count) : count{count} {
    }

    /**
     * Constructor implicit pentru declararea neinitializata
     */
    ReportDTO() = default;


    /**
    * Functia returneaza frecventa tipului de discipline curente
    * @return frecventa tipului de discipline curente
    */
    [[nodiscard]] int getCount() const noexcept;
};
