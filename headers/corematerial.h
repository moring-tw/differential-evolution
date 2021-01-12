#pragma once
#ifndef EA_HEADERS_COREMATERIAL_H_
#define EA_HEADERS_COREMATERIAL_H_

#include <map>
#include <string>
#include <iostream>

namespace evolutionalgorithm {
    namespace corematerial {
        enum class Algorithm : unsigned int {
            kDE, kSaDE, kSHADE, kLHDDE, kCustom = 128
        };

        //for more information, see: https://stackoverflow.com/questions/18195312/what-happens-if-you-static-cast-invalid-value-to-enum-class.
        template <typename T>
        static T operator+(T& a1, T& a2) {
            using under = typename std::underlying_type<T>::type;
            T res = static_cast<T>(static_cast<under>(a1) + static_cast<under>(a2));
            return res;
        }

        template <typename T>
        static T operator-(T& a1, T& a2) {
            using under = typename std::underlying_type<T>::type;
            T res = static_cast<T>(static_cast<under>(a1) - static_cast<under>(a2));
            return res;
        }

        template <typename T>
        static T operator&(const T& a1, const T& a2) {
            using under = typename std::underlying_type<T>::type;
            T res = static_cast<T>((static_cast<under>(a1) & static_cast<under>(a2)));
            return res;
        }

        template <typename T>
        static T operator&(const size_t a1, const T& a2) {
            using under = typename std::underlying_type<T>::type;
            T res = static_cast<T>(a1 & static_cast<under>(a2));
            return res;
        }

        /*template <typename T, typename U>
        static bool operator!=(const T& a1, U a2) {
            T t1 = static_cast<T>(a2);
            bool res = (t1 != a1);
            return res;
        }*/

        template <typename T>
        static bool operator!=(const T& a1, const int a2) {
            using under = typename std::underlying_type<T>::type;
            bool res = (static_cast<under>(a1) != a2);
            return res;
        }

        template <typename T>
        static bool operator!=(const size_t a1, const T& a2) {
            return (a2 != static_cast<T>(a1));
        }

        template <typename T>
        static void operator<<=(T& a1, int) {
            using under = typename std::underlying_type<T>::type;
            under temp = static_cast<under>(a1);
            a1 = static_cast<T>((temp <<= 1));
        }

        template <typename T>
        static bool operator==(const T& left, int right) {
            using under = typename std::underlying_type<T>::type;
            under temp = static_cast<under>(left);
            return (temp == right);
        }

        template <typename T>
        static bool operator>(const T& left, const int right) {
            using under = typename std::underlying_type<T>::type;
            return static_cast<under>(left) > static_cast<under>(right);
        }

        template <typename T>
        static void operator+=(T& a1, const T& a2) {
            using under = typename std::underlying_type<T>::type;
            under temp = static_cast<under>(a1);
            a1 = static_cast<T>(static_cast<under>(a1) + static_cast<under>(a2));
        }

        template <typename T>
        static void operator-=(T& a1, const T& a2) {
            using under = typename std::underlying_type<T>::type;
            a1 = static_cast<T>(static_cast<under>(a1) - static_cast<under>(a2));
        }

        static const std::map<std::string, Algorithm> kAlgorithmMap = {
            {"kDE", Algorithm::kDE},
            {"kSaDE", Algorithm::kSaDE},
            {"kSHADE", Algorithm::kSHADE},
            {"kLHDDE", Algorithm::kLHDDE},
            {"kCustom", Algorithm::kCustom}
        };
        enum class InitialPopulation : unsigned int {
            kRandom, kLHD, kLHDetect
        };
        static const std::map<std::string, InitialPopulation> kInitialPopulationMap = {
            {"kRandom", InitialPopulation::kRandom},
            {"kLHD", InitialPopulation::kLHD},
            {"kLHDetect", InitialPopulation::kLHDetect}
        };

        enum class ParametersControl : unsigned int {
            UNSET = 0x00, kCR = 0x01, kF = 0x02, kK = 0x04, kP = 0x08
        };
        static const std::map<std::string, ParametersControl> kParametersControlMap{
            {"kCR", ParametersControl::kCR},
            {"kF",ParametersControl::kF},
            {"kK", ParametersControl::kK},
            {"kP", ParametersControl::kP}
        };

        enum class Memory : unsigned int {
            UNSET = 0x00,
            kArchive = 0x01,
            kNPRank = 0x02,
            kEvolutionPath = 0x04
        };
        static const std::map<std::string, Memory> kMemoryMap = {
            {"kArchive", Memory::kArchive},
            {"kNPRank", Memory::kNPRank},
            {"kEvolutionPath", Memory::kEvolutionPath}
        };
        enum class Archive : unsigned int {
            UNSET = 0, kSHADE_Archive
        };
        static const std::map<std::string, Archive> kArchiveMap = {
            {"kSHADE_Archive", Archive::kSHADE_Archive}
        };

        enum class MemoryCR : unsigned int {
            kSaDE_CR, kSHADE_CR
        };
        static const std::map<std::string, MemoryCR> kMemoryCRMap = {
            {"kSaDE_CR", MemoryCR::kSaDE_CR},
            {"kSHADE_CR", MemoryCR::kSHADE_CR}
        };

        enum class MemoryCR_Setting : unsigned int {
            UNSET = 0x00,
            kMemoryByEachStrategy = 0x01
        };
        static const std::map<std::string, MemoryCR_Setting> kMemoryCR_SettingMap = {
            {"kMemoryByEachStrategy", MemoryCR_Setting::kMemoryByEachStrategy}
        };

        enum class MemoryF : unsigned int {
            kSHADE_F
        };
        static const std::map<std::string, MemoryF> kMemoryFMap = {
            {"kSHADE_F", MemoryF::kSHADE_F}
        };

        enum class ParametersControlMethod : unsigned int {
            UNSET = 0x00,
            kNormalF = 0x01,
            kRandomP = 0x02,
            kArchiveSizeEqualNP = 0x04,
            kMemoryCR = 0x08,
            kMemoryF = 0x10
        };
        static const std::map<std::string, ParametersControlMethod> kParametersControlMethodMap = {
            {"kNormalF", ParametersControlMethod::kNormalF},
            {"kRandomP", ParametersControlMethod::kRandomP},
            {"kArchiveSizeEqualNP", ParametersControlMethod::kArchiveSizeEqualNP},
            {"kMemoryCR", ParametersControlMethod::kMemoryCR},
            {"kMemoryF", ParametersControlMethod::kMemoryF}
        };
        enum class MutantAndCrossover : unsigned int {
            UNSET = 0x00,
            kRand = 0x01,// Change value of KRand will cause counting error, see readconfig.cpp -> ImplicitHandler().
            kBest = 0x02,
            kCurToRand = 0x04,
            kCurToBest = 0x08,
            kCurToPBest = 0x10
        };
        static const std::map<std::string, MutantAndCrossover> kMutantAndCrossoverMap = {
            {"kRand", MutantAndCrossover::kRand},
            {"kBest", MutantAndCrossover::kBest},
            {"kCurToRand", MutantAndCrossover::kCurToRand},
            {"kCurToBest", MutantAndCrossover::kCurToBest},
            {"kCurToPBest", MutantAndCrossover::kCurToPBest}
        };

        enum class StrategiesSelection : unsigned int {
            kSaDE_ss
        };
        static const std::map<std::string, StrategiesSelection> kStrategiesSelectionMap = {
            {"kSaDE_ss", StrategiesSelection::kSaDE_ss}
        };

        enum class Selection : unsigned int {
            kCompetition
        };
        static const std::map<std::string, Selection> kSelectionMap = {
            {"kCompetition", Selection::kCompetition}
        };

        enum class StopCriterion : unsigned int {
            UNSET = 0x00,
            kMaxFE = 0x01,
            kMaxGeneration = 0x02,
            kReachOptimal = 0x04
        };
        static const std::map<std::string, StopCriterion> kStopCriterionMap = {
            {"kMaxFE", StopCriterion::kMaxFE},
            {"kMaxGeneration", StopCriterion::kMaxGeneration},
            {"kReachOptimal", StopCriterion::kReachOptimal}
        };
        enum class Debug : unsigned int {
            UNSET = 0x00,
            kInitialPopulation = 0x01,
            kInitialFitness = 0x02,
            kMutantAndCrossover = 0x04,
            kSelection = 0x08,
            kReadConfig = 0x10
        };
        static const std::map<std::string, Debug > kDebugMap = {
            {"kInitialPopulation", Debug::kInitialPopulation},
            {"kInitialFitness", Debug::kInitialFitness},
            {"kMutantAndCrossover", Debug::kMutantAndCrossover},
            {"kSelection", Debug::kSelection},
            {"kReadConfig", Debug::kReadConfig}
        };

        enum class OutBoundHandler : unsigned int {
            kRerandomDimension, kBackToBound, kHalfBoundDistance, kRerandomIndividual
        };
        static const std::map<std::string, OutBoundHandler> kOutBoundHandlerMap = {
            {"kRerandomDimension", OutBoundHandler::kRerandomDimension},
            {"kBackToBound", OutBoundHandler::kBackToBound},
            {"kHalfBoundDistance", OutBoundHandler::kHalfBoundDistance},
            {"kRerandomIndividual", OutBoundHandler::kRerandomIndividual}
        };
    } // namespace corematerial
} // namespace evolutionalgorithm
#endif // EA_HEADERS_COREMATERIAL_H_
