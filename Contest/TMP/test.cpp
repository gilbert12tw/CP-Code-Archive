if (noffH.initData.size > 0) {
    DEBUG(dbgAddr, "Initializing data segment.");
    DEBUG(dbgAddr, noffH.initData.virtualAddr << ", " << noffH.initData.size);
    int start = noffH.initData.virtualAddr / PageSize;
    int end = (noffH.initData.virtualAddr + noffH.initData.size - 1) / PageSize;
    int currentAddr = noffH.initData.virtualAddr;
    int offset = noffH.initData.inFileAddr - noffH.initData.virtualAddr;
    for(int i = start; i <= end; i++) {
        int nextPageStartAddr = PageSize * (i + 1);
        int noffLastAddr = noffH.initData.virtualAddr + noffH.initData.size;
        int numBytes = min(nextPageStartAddr, noffLastAddr) - currentAddr;
        executable->ReadAt(
                &kernel->machine->mainMemory[pageTable[i].physicalPage * PageSize + currentAddr % PageSize],
                numBytes,
                offset + currentAddr
                );
        currentAddr = PageSize * (i + 1);
    }
}

