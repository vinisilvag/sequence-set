#include "Testing.cpp"

using namespace std;

int main() {
    Report *bMaisReport = new Report("bmais-report.csv");
    Report *sequenceSetReport = new Report("ss-report.csv");

    for (int i = 1; i <= 20; i++) {
        for (int j = 0; j < 5; j++) {
            int volumeDados = 100 * i;

            Testing *testing = new Testing(volumeDados, 100000, bMaisReport, sequenceSetReport);

            testing->testBmais(i);
            testing->testSequenceSet(i);
        }
    }

    bMaisReport->generateCsv();
    sequenceSetReport->generateCsv();

    return 0;
}