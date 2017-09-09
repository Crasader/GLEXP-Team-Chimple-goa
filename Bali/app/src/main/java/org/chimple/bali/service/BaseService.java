package org.chimple.bali.service;

import android.content.Context;

import org.chimple.bali.ftp.FtpManager;
import org.chimple.bali.operation.OpState;
import org.chimple.bali.operation.OperationListener;
import org.chimple.bali.operation.OperationManager;

/**
 * Created by shyamalupadhyaya on 08/09/17.
 */

public abstract class BaseService implements OperationListener {
    private ThreadManager threadManager;
    private OperationManager operationManager;
    private FtpManager ftpManager;

    public void setThreadManager(ThreadManager threadManager) {
        this.threadManager = threadManager;
    }

    public ThreadManager getThreadManager() {
        return this.threadManager;
    }

    public void setFtpManager(FtpManager ftpManager) {
        this.ftpManager = ftpManager;
    }

    public FtpManager getFtpManager() {
        return this.ftpManager;
    }

    protected void runInBackground(ServiceRunnable runnable) {
        threadManager.runInBackground(runnable);
    }

    protected void runOnMainThread(Runnable runnable)
    {
        threadManager.runOnMainThread(runnable);
    }

    public OperationManager getOperationManager() {
        return operationManager;
    }

    public void initialize(Context context) {
        operationManager = new OperationManager(context, this, threadManager);
    }

    /**
     * Subclass needs to override this if it wants to handle operation state.
     */
    public abstract void handleOperation(OpState opState);
}
