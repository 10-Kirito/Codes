#ifndef _TOOLS_H
#define _TOOLS_H

bool Compare_Pid(const Process& a, const Process& b) {
    return a.getPid() <= b.getPid();
}
#ifdef PRIORITY
bool Compare_Priority(const Process& a, const Process& b) {
    return a.getPriority() >= b.getPriority();
}
#endif

#endif // !_TOOLS_H

