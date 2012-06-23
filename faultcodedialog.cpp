#include <QMessageBox>
#include "faultcodedialog.h"

/**
 * Constructor. Creates the fault code list, creates widgets, and sets them
 *  appropriately.
 */
FaultCodeDialog::FaultCodeDialog(QString title, Comm14CUXFaultCodes faults):
    rows(5)
{
    qRegisterMetaType<Comm14CUXFaultCodes>("Comm14CUXFaultCodes");
    this->setWindowTitle(title);
    populateFaultList();
    setupWidgets();
    lightLEDs(faults);
}

/**
 * Destructor.
 */
FaultCodeDialog::~FaultCodeDialog()
{
}

/**
 * Displays a message box with an error message about failure to clear fault codes.
 */
void FaultCodeDialog::onFaultClearFailure()
{
    QMessageBox::warning(this, "Error", "Unable to clear fault codes. Check connections.",
        QMessageBox::Ok);
}

/**
 * Displays a message box indicating that fault codes were successfully cleared, and
 * sets the fault LEDs to match the new set of codes.
 */
void FaultCodeDialog::onFaultClearSuccess(Comm14CUXFaultCodes faultCodes)
{
    QMessageBox::information(this, "Success", "Successfully cleared fault codes.", QMessageBox::Ok);
    lightLEDs(faultCodes);
}

/**
 * Creates the list of possible fault codes, and their descriptions.
 */
void FaultCodeDialog::populateFaultList()
{
    faultNames.insert(FaultCode_ECUMemoryCheck, QString("ECU Memory Check"));
    faultNames.insert(FaultCode_LambdaSensorLeft, QString("Lambda Sensor (left)"));
    faultNames.insert(FaultCode_LambdaSensorRight, QString("Lambda Sensor (right)"));
    faultNames.insert(FaultCode_MisfireLeft, QString("Misfire (left)"));
    faultNames.insert(FaultCode_MisfireRight, QString("Misfire (right)"));
    faultNames.insert(FaultCode_AirflowMeter, QString("Airflow Meter"));
    faultNames.insert(FaultCode_TuneResistor, QString("Tune Resistor out of range"));
    faultNames.insert(FaultCode_InjectorLeft, QString("Injector Left"));
    faultNames.insert(FaultCode_InjectorRight, QString("Injector Right"));
    faultNames.insert(FaultCode_CoolantTempSensor, QString("Coolant Temp Sensor"));
    faultNames.insert(FaultCode_ThrottlePot, QString("Throttle Pot"));
    faultNames.insert(FaultCode_ThrottlePotHiMAFLo, QString("Throttle Pot Hi / MAF Lo"));
    faultNames.insert(FaultCode_ThrottlePotLoMAFHi, QString("Throttle Pot Lo / MAF Hi"));
    faultNames.insert(FaultCode_PurgeValveLeak, QString("Purge Valve Leak"));
    faultNames.insert(FaultCode_MixtureTooLean, QString("Mixture too lean"));
    faultNames.insert(FaultCode_IntakeAirLeak, QString("Intake air leak"));
    faultNames.insert(FaultCode_LowFuelPressure, QString("Low fuel pressure"));
    faultNames.insert(FaultCode_IdleStepper, QString("Idle Stepper"));
    faultNames.insert(FaultCode_RoadSpeedSensor, QString("Road Speed Sensor"));
    faultNames.insert(FaultCode_NeutralSwitch, QString("Neutral Switch"));
    faultNames.insert(FaultCode_FuelPressureOrLeak, QString("Ambiguous: low fuel pressure or air leak"));
    faultNames.insert(FaultCode_FuelTempSensor, QString("Fuel Temp Sensor"));
    faultNames.insert(FaultCode_BatteryDisconnected, QString("Battery Disconnected"));
    faultNames.insert(FaultCode_ECMMemoryCleared, QString("ECM Memory Cleared"));
}

/**
 * Creates, sets up, and places an LED widget for each of the possible fault
 * codes.
 */
void FaultCodeDialog::setupWidgets()
{
    grid = new QGridLayout(this);

    QLedIndicator *currentLed;
    QLabel *currentLabel;
    QList<FaultCode> faultTypes = faultNames.uniqueKeys();
    int position = 0;
    foreach (FaultCode fault, faultTypes)
    {
        // create a new LED and set its color to red
        currentLed = new QLedIndicator(this);
        currentLed->setOnColor1(QColor(255, 0, 0));
        currentLed->setOnColor2(QColor(176, 0, 2));
        currentLed->setOffColor1(QColor(20, 0, 0));
        currentLed->setOffColor2(QColor(90, 0, 2));
        currentLed->setDisabled(true);
        faultLights.insert(fault, currentLed);

        // create a label for this fault code
        currentLabel = new QLabel(faultNames[fault], this);
        faultLabels.insert(fault, currentLabel);

        grid->addWidget(currentLed, position%rows, position/rows*2, Qt::AlignRight);
        grid->addWidget(currentLabel, position%rows, (position/rows*2)+1, Qt::AlignLeft);

        position++;
    }

    clearButton = new QPushButton("Clear codes", this);
    grid->addWidget(clearButton, rows-1, (position/rows*2)+1, Qt::AlignCenter);
    connect(clearButton, SIGNAL(clicked()), this, SIGNAL(clearFaultCodes()));

    closeButton = new QPushButton("Close", this);
    grid->addWidget(closeButton, rows, (position/rows*2)+1, Qt::AlignCenter);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(accept()));
}

/**
 * Lights the appropriate fault lamps based on the provided faultcode structure.
 * @param faults Fault codes read from the 14CUX
 */
void FaultCodeDialog::lightLEDs(Comm14CUXFaultCodes faults)
{
    faultLights[FaultCode_ECUMemoryCheck]->setChecked(faults.ECU_Memory_Check);
    faultLights[FaultCode_LambdaSensorLeft]->setChecked(faults.Lambda_Sensor_Left);
    faultLights[FaultCode_LambdaSensorRight]->setChecked(faults.Lambda_Sensor_Right);
    faultLights[FaultCode_MisfireLeft]->setChecked(faults.Misfire_Left_Bank);
    faultLights[FaultCode_MisfireRight]->setChecked(faults.Misfire_Right_Bank);
    faultLights[FaultCode_AirflowMeter]->setChecked(faults.Airflow_Meter);
    faultLights[FaultCode_TuneResistor]->setChecked(faults.Tune_Resistor_Out_of_Range);
    faultLights[FaultCode_InjectorLeft]->setChecked(faults.Injector_Left_Bank);
    faultLights[FaultCode_InjectorRight]->setChecked(faults.Injector_Right_Bank);
    faultLights[FaultCode_CoolantTempSensor]->setChecked(faults.Coolant_Temp_Sensor);
    faultLights[FaultCode_ThrottlePot]->setChecked(faults.Throttle_Pot);
    faultLights[FaultCode_ThrottlePotHiMAFLo]->setChecked(faults.Throttle_Pot_Hi_MAF_Lo);
    faultLights[FaultCode_ThrottlePotLoMAFHi]->setChecked(faults.Throttle_Pot_Lo_MAF_Hi);
    faultLights[FaultCode_PurgeValveLeak]->setChecked(faults.Purge_Valve_Leak);
    faultLights[FaultCode_MixtureTooLean]->setChecked(faults.Mixture_Too_Lean);
    faultLights[FaultCode_IntakeAirLeak]->setChecked(faults.Intake_Air_Leak);
    faultLights[FaultCode_LowFuelPressure]->setChecked(faults.Low_Fuel_Pressure);
    faultLights[FaultCode_IdleStepper]->setChecked(faults.Idle_Valve_Stepper_Motor);
    faultLights[FaultCode_RoadSpeedSensor]->setChecked(faults.Road_Speed_Sensor);
    faultLights[FaultCode_NeutralSwitch]->setChecked(faults.Neutral_Switch);
    faultLights[FaultCode_FuelPressureOrLeak]->setChecked(faults.Low_Fuel_Pressure_or_Air_Leak);
    faultLights[FaultCode_FuelTempSensor]->setChecked(faults.Fuel_Temp_Sensor);
    faultLights[FaultCode_BatteryDisconnected]->setChecked(faults.Battery_Disconnected);
    faultLights[FaultCode_ECMMemoryCleared]->setChecked(faults.ECM_Memory_Cleared);
}

/**
 * Closes the dialog.
 */
void FaultCodeDialog::accept()
{
    done(QDialog::Accepted);
}

