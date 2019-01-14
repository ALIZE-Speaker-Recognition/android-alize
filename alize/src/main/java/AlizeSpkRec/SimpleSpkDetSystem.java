package AlizeSpkRec;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class SimpleSpkDetSystem
{
    static
    {
        System.loadLibrary("alize-native");
    }

    /**
     * Constructor that initialize the Alize-system with an InputStream.
     * @param configInput The InputStream that contains the configFile.
     * @param workdirPath Path to the working directory.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public SimpleSpkDetSystem(InputStream configInput, String workdirPath) throws AlizeException, IOException
    {
        workdir = new File(workdirPath);
        File tmpConfigFile = transferDataToWorkdir(configInput,"config",".cfg");
        initSystem(tmpConfigFile.getName(), workdirPath);
        tmpConfigFile.delete();
    }

    /**
     * Constructor that initialize the Alize-system with a config file.
     * @param configFilename The config file that will contains variables to initialise the Alize-system.
     * @param workdirPath Path to the working directory.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public SimpleSpkDetSystem(String configFilename, String workdirPath) throws AlizeException
    {
        workdir = new File(workdirPath);
        initSystem(configFilename, workdirPath);
    }

    /**
     * Method call when the system decide to destroy an instance of Alize.
     * @throws Throwable Thrown when anything wrong arrived.
     */
    protected void finalize() throws Throwable {
        releaseSystem();
        super.finalize();
    }

    /**
     * Return the number of features presents in the Alize-system.
     * @return The number of features.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native long featureCount() throws AlizeException;

    /**
     * Return the number of speakers presents in the Alize-system.
     * @return The number of speakers.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native long speakerCount() throws AlizeException;

    /**
     * Allows to know if the UBM is loaded in the system.
     * @return True if yes, False if not.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native boolean isUBMLoaded() throws AlizeException;

    /**
     * Return the list of the speakers IDs presents in the system.
     * @return The list of the speakers IDs.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native String[] speakerIDs() throws AlizeException;

    /**
     * Set an option of the configuration 'name' to 'value'.
     * @param name An option of the configuration.
     * @param value His value.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void setOption(String name, String value) throws AlizeException;

    /*! \fn void SimpleSpkDetSystem::decisionThreshold()
     *  \brief  Returns the theshold used in verifySpeaker() and identifySpeaker()
     *          Only speakers with scores higher than the decision threshold will be
     *          considered a match for the target speaker.
     */
    public native double decisionThreshold() throws AlizeException;

    /*! \fn void SimpleSpkDetSystem::setDecisionThreshold(double newValue)
     *  \brief  Sets the theshold used in verifySpeaker() and identifySpeaker()
     *          Only speakers with scores higher than the decision threshold will be
     *          considered a match for the target speaker.
     *
     *  \param[in]      newValue        the new decision threshold
     */
    public native void setDecisionThreshold(double newValue) throws AlizeException;

    /**
     * Receive an audio signal as 16-bit signed integer linear PCM, parameterize it and add it to the feature server.
     * @param linearPCMSamples Audio data, as 16-bit signed integer linear PCM.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void addAudio(short[] linearPCMSamples) throws AlizeException;

    /**
     * Load an audio file, parameterize it and add it to the feature server.
     * @param filename Filename of the acoustic parameters to load.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public native void addAudio(String filename) throws AlizeException, IOException;

    /**
     * This method is used to convert InputStream file to a filename and call addAudio(String filename).
     * @param audioDataStream The audio data contained in the InputStream.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public void addAudio(InputStream audioDataStream) throws AlizeException, IOException
    {
        File tmpAudioFile = transferDataToWorkdir(audioDataStream,"tmp_audio",".audio");
        addAudio(tmpAudioFile.getAbsolutePath());
        tmpAudioFile.delete();
    }

    /**
     * Receive an audio signal (following the format specified in the configuration), parameterize it and add it to the feature server.
     * @param audioData The audio data.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public native void addAudio(byte[] audioData) throws AlizeException, IOException;

    /**
     * Save the current audio present in the system in a file.
     * @param filename The name of the save file.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void saveAudio(String filename) throws AlizeException;

    /**
     * Remove all the audio data.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void resetAudio() throws AlizeException;

    /**
     * Add features received from the client.
     * @param featureData The feature data.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public native void addFeatures(byte[] featureData) throws AlizeException, IOException;

    /**
     * Add features from a feature file.
     * @param filename The name of the feature file.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public native void addFeatures(String filename) throws AlizeException, IOException;

    /**
     * This method is used to convert InputStream file to a filename and call addFeatures(String filename).
     * @param featureDataStream The features data contained in the InputStream.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public void addFeatures(InputStream featureDataStream) throws AlizeException, IOException
    {
        File tmpFeatureFile = transferDataToWorkdir(featureDataStream,"tmp_features",".prm");
        addFeatures(tmpFeatureFile.getAbsolutePath());
        tmpFeatureFile.delete();
    }

    /**
     * Save the content of the feature server to a file.
     * @param filename The name of the file.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void saveFeatures(String filename) throws AlizeException;

    /**
     * Remove all the features from the feature server.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void resetFeatures() throws AlizeException;

    /**
     * Load the world model from the file.
     * @param filename The name of the file.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void loadBackgroundModel(String filename) throws AlizeException;

    /**
     * This method is used to convert InputStream file to a filename and call loadBackgroundModel(String filename).
     * @param model The world model in an InputStream.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public void loadBackgroundModel(InputStream model) throws AlizeException, IOException
    {
        File tmpModelFile = transferDataToWorkdir(model,"tmp_world",".gmm");
        loadBackgroundModel(tmpModelFile.getAbsolutePath());
        tmpModelFile.delete();
    }

    /**
     * Load the speaker Id mixture from the file.
     * @param speakerId Speaker Id of the mixture to load.
     * @param filename Filename to load the mixture.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public native void loadSpeakerModel(String speakerId, String filename) throws AlizeException, IOException;

    /**
     * This method is used to convert InputStream model to a filename and call loadSpeakerModel(String speakerId, String filename).
     * @param speakerId Speaker Id of the mixture to load.
     * @param model The InputStream that contains the mixture to load.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     * @throws IOException Thrown when there are problems with the paths.
     */
    public void loadSpeakerModel(String speakerId, InputStream model) throws AlizeException, IOException
    {
        File tmpModelFile = transferDataToWorkdir(model,"tmp_"+speakerId,".gmm");
        loadSpeakerModel(speakerId, tmpModelFile.getAbsolutePath());
        tmpModelFile.delete();
    }

    /**
     * Save the speaker Id mixture to the file.
     * @param speakerId The speaker Id of the mixture to save.
     * @param filename The filename to save the mixture.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void saveSpeakerModel(String speakerId, String filename) throws AlizeException;

    /**
     * Delete the mixture with Id speakerId.
     * @param speakerId The speaker Id of the mixture to delete.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void removeSpeaker(String speakerId) throws AlizeException;

    /**
     * Reset all speakers mixtures, leaving only the world model
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void removeAllSpeakers() throws AlizeException;

    /**
     * Train a mixture with the features in memory and assign it the speakerId.
     * @param speakerId The speaker Id to assign at the mixture.
     * @throws IdAlreadyExistsException Thrown when the speakerId already exists.
     */
    public native void createSpeakerModel(String speakerId) throws IdAlreadyExistsException;

    /**
     * Adapt the speaker Id mixture with the features currently in memory.
     * @param speakerId The speaker Id use to modify his features.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void adaptSpeakerModel(String speakerId) throws AlizeException;

    /**
     * The class SpkRecResult is used to contain results of method,
     * because we cannot store results in variables with references like in C++.
     */
    public static class SpkRecResult
    {
        public boolean match;
        public float score;
        public String speakerId;

        public SpkRecResult() {}
    }

    /**
     * Check the features in memory against a given user with score accumulation at false by default.
     * @param targetSpeakerId The targeted speaker Id.
     * @return Return an instance of SpkRecResult that contains results of the method.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public SpkRecResult verifySpeaker(String targetSpeakerId) throws AlizeException {
        return verifySpeaker(targetSpeakerId, false);
    }

    /**
     * Check the features in memory against a given user.
     * @param targetSpeakerId The targeted speaker Id.
     * @param withScoreAccumulation Combine the score with previous scores for this speaker.
     * @return Return an instance of SpkRecResult that contains results of the method.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    private native SpkRecResult verifySpeaker(String targetSpeakerId, boolean withScoreAccumulation) throws AlizeException;

    /**
     * Check the features in memory against all the users and find the best match, with score accumulation at false by default.
     * @return Return an instance of SpkRecResult that contains results of the method.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public SpkRecResult identifySpeaker() throws AlizeException {
        return identifySpeaker(false);
    }

    /**
     * Check the features in memory against all the users and find the best match.
     * @param withScoreAccumulation Combine the score with previous scores for this speaker.
     * @return Return an instance of SpkRecResult that contains results of the method.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native SpkRecResult identifySpeaker(boolean withScoreAccumulation) throws AlizeException;

    /**
     * Reset the score accumulator for the speaker speakerId.
     * @param speakerId The speaker that we want to reset his score accumulator.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void resetAccumulatedScore(String speakerId) throws AlizeException;

    /**
     * Reset the score accumulator for all the speakers.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    public native void resetAllAccumulatedScores() throws AlizeException;

    /**
     * Instance of the system in C++.
     */
    private long nativeSystemPtr = 0;
    /**
     * The file that contains the working directory.
     */
    private File workdir;

    /**
     * Method that initialize the nativeSystemPtr variable.
     * @param configFilename The file that contains configurations for the Alize-system.
     * @param workdirPath The path of the working directory.
     * @throws AlizeException An homemade exception corresponding to the alize-system.
     */
    private native void initSystem(String configFilename, String workdirPath) throws AlizeException;

    /**
     * Method that allows to release the system (nativeSystemPtr variable).
     */
    private native void releaseSystem();

    /**
     * Allows to transfer data to the working directory.
     * @param dataInput The data to transfer.
     * @param prefix The prefix of the file.
     * @param suffix The suffix of the file.
     * @return Return the file that contains all the data.
     * @throws IOException Thrown when there are problems with the paths.
     */
    private File transferDataToWorkdir(InputStream dataInput, String prefix, String suffix) throws IOException
    {
        File tmpFile = File.createTempFile(prefix,suffix,workdir);
        OutputStream dataOutput = new BufferedOutputStream(new FileOutputStream(tmpFile));
        int b;
        while ((b = dataInput.read()) != -1)
        {
            dataOutput.write(b);
        }
        dataOutput.close();
        return tmpFile;
    }

}