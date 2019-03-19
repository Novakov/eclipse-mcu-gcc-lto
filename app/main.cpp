#include <em_chip.h>
#include <em_gpio.h>
#include <cstdint>
#include <em_system.h>
#include <em_cmu.h>

template <GPIO_Port_TypeDef TPort, std::uint16_t TPinNumber>
struct PinLocation
{
    /** @brief Selected port */
    static constexpr auto Port = TPort;
    /** @brief Selected pin number */
    static constexpr auto PinNumber = TPinNumber;
};

namespace io_map
{
struct XTAL
{
    struct HF
    {
        using Pin1 = PinLocation<gpioPortB, 13>;
        using Pin2 = PinLocation<gpioPortB, 14>;
    };

    struct LF
    {
        using Pin1 = PinLocation<gpioPortB, 7>;
        using Pin2 = PinLocation<gpioPortB, 8>;
    };
};
} // namespace io_map

void SetupHardware(void)
{
    CMU_ClockEnable(cmuClock_GPIO, true);

    // LFXTAL
    GPIO_PinModeSet(io_map::XTAL::LF::Pin1::Port, io_map::XTAL::LF::Pin1::PinNumber, gpioModeDisabled, 0);
    GPIO_PinModeSet(io_map::XTAL::LF::Pin2::Port, io_map::XTAL::LF::Pin2::PinNumber, gpioModeDisabled, 0);

    // HFXTAL
    GPIO_PinModeSet(io_map::XTAL::HF::Pin1::Port, io_map::XTAL::HF::Pin1::PinNumber, gpioModeDisabled, 0);
    GPIO_PinModeSet(io_map::XTAL::HF::Pin2::Port, io_map::XTAL::HF::Pin2::PinNumber, gpioModeDisabled, 0);

    CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_HFCLKLE);
    CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_HFCLKLE);

    CMU_OscillatorEnable(cmuOsc_HFXO, true, true);
    CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
    CMU_OscillatorEnable(cmuOsc_HFRCO, false, true);
}

int main()
{
    SCB->VTOR = 0x00080000;

    CHIP_Init();

    SetupHardware();
    return 0;
}
