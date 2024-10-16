#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <memory>

const double PI = 3.14159265358979323846;

class Waveform {
public:
    virtual double generate(double time) const = 0;
    virtual void setFrequency(double frequency) { m_frequency = frequency; }
    virtual void setAmplitude(double amplitude) { m_amplitude = amplitude; }
    virtual void setPhase(double phase) { m_phase = phase; }

protected:
    double m_frequency = 1.0;
    double m_amplitude = 1.0;
    double m_phase = 0.0;
};

class SineWave : public Waveform {
public:
    double generate(double time) const override {
        return m_amplitude * std::sin(2 * PI * m_frequency * time + m_phase);
    }
};

class SquareWave : public Waveform {
public:
    double generate(double time) const override {
        double t = std::fmod(time * m_frequency + m_phase / (2 * PI), 1.0);
        return m_amplitude * (t < 0.5 ? 1.0 : -1.0);
    }
};

class TriangleWave : public Waveform {
public:
    double generate(double time) const override {
        double t = std::fmod(time * m_frequency + m_phase / (2 * PI), 1.0);
        return m_amplitude * (t < 0.5 ? 4 * t - 1 : 3 - 4 * t);
    }
};

std::vector<std::pair<double, double>> generateWaveformData(const Waveform& waveform, double duration, int sampleRate) {
    std::vector<std::pair<double, double>> data;
    double timeStep = 1.0 / sampleRate;
    for (int i = 0; i <= duration * sampleRate; ++i) {
        double time = i * timeStep;
        data.emplace_back(time, waveform.generate(time));
    }
    return data;
}

void saveToCSV(const std::vector<std::pair<double, double>>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    file << "Time,Amplitude\n";
    for (const auto& point : data) {
        file << point.first << "," << point.second << "\n";
    }
    file.close();
}

std::unique_ptr<Waveform> createWaveform(char type) {
    switch (type) {
        case 's': return std::make_unique<SineWave>();
        case 'q': return std::make_unique<SquareWave>();
        case 't': return std::make_unique<TriangleWave>();
        default: return nullptr;
    }
}

int main() {
    char waveformType;
    double frequency, amplitude, phase, duration;
    int sampleRate;

    std::cout << "Enter waveform type (s for Sine, q for Square, t for Triangle): ";
    std::cin >> waveformType;

    std::cout << "Enter frequency (Hz): ";
    std::cin >> frequency;

    std::cout << "Enter amplitude: ";
    std::cin >> amplitude;

    std::cout << "Enter phase shift (radians): ";
    std::cin >> phase;

    std::cout << "Enter duration (seconds): ";
    std::cin >> duration;

    std::cout << "Enter sample rate (samples/second): ";
    std::cin >> sampleRate;

    auto waveform = createWaveform(waveformType);
    if (!waveform) {
        std::cerr << "Invalid waveform type." << std::endl;
        return 1;
    }

    waveform->setFrequency(frequency);
    waveform->setAmplitude(amplitude);
    waveform->setPhase(phase);

    auto data = generateWaveformData(*waveform, duration, sampleRate);
    saveToCSV(data, "waveform_data.csv");

    std::cout << "Waveform data saved to waveform_data.csv" << std::endl;

    return 0;
}