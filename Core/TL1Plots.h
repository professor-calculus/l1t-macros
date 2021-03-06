#ifndef TL1PLOTS_H
#define TL1PLOTS_H

#include <string>
#include <memory>

#include <sys/types.h>
#include <sys/stat.h>

#include <TDatime.h>

class TL1Plots
{
    public:
        TL1Plots();

        virtual void InitPlots() = 0;
        virtual void Fill(const double & xVal, const double & yVal) = 0;
        virtual void DrawPlots() = 0;

        virtual void SetSample(const std::string & sampleName, const std::string & sampleTitle);
        virtual void SetTrigger(const std::string & triggerName, const std::string & triggerTitle);
        virtual void SetRun(const std::string & run);
        virtual void SetOutName(const std::string & outName);
        virtual void SetOutDir(const std::string & outDir);

        std::string GetDate() const;

    protected:
        std::string GetSampleName() const;
        std::string GetTriggerName() const;
        std::string GetRun() const;
        std::string GetSampleTitle() const;
        std::string GetTriggerTitle() const;
        std::string GetOutName() const;
        std::string GetOutDir() const;

    private:
        std::shared_ptr<TDatime> fDate;
        std::string fSampleName, fTriggerName, fRun;
        std::string fSampleTitle, fTriggerTitle;
        std::string fOutName, fOutDir;

};

TL1Plots::TL1Plots() :
    fDate(new TDatime())
{
}

void TL1Plots::SetSample(const std::string & sampleName, const std::string & sampleTitle)
{
    fSampleName = sampleName;
    fSampleTitle = sampleTitle;
}

void TL1Plots::SetTrigger(const std::string & triggerName, const std::string & triggerTitle)
{
    fTriggerName = triggerName;
    fTriggerTitle = triggerTitle;
}

void TL1Plots::SetRun(const std::string & run)
{
    fRun = run;
}

void TL1Plots::SetOutName(const std::string & outName)
{
    fOutName = outName;
}

void TL1Plots::SetOutDir(const std::string & outDir)
{
    fOutDir = outDir;
}

std::string TL1Plots::GetSampleName() const
{
    return fSampleName;
}

std::string TL1Plots::GetTriggerName() const
{
    return fTriggerName;
}

std::string TL1Plots::GetRun() const
{
    return fRun;
}

std::string TL1Plots::GetSampleTitle() const
{
    return fSampleTitle;
}

std::string TL1Plots::GetTriggerTitle() const
{
    return fTriggerTitle;
}

std::string TL1Plots::GetOutName() const
{
    return fOutName;
}

std::string TL1Plots::GetOutDir() const
{
    return fOutDir;
}

std::string TL1Plots::GetDate() const
{
    return std::to_string(fDate->GetDate());
}

#endif
