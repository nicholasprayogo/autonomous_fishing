
"use strict";

let WaypointPush = require('./WaypointPush.js')
let WaypointSetCurrent = require('./WaypointSetCurrent.js')
let ParamSet = require('./ParamSet.js')
let LogRequestEnd = require('./LogRequestEnd.js')
let FileList = require('./FileList.js')
let FileRemove = require('./FileRemove.js')
let FileOpen = require('./FileOpen.js')
let MountConfigure = require('./MountConfigure.js')
let SetMode = require('./SetMode.js')
let WaypointClear = require('./WaypointClear.js')
let FileWrite = require('./FileWrite.js')
let FileMakeDir = require('./FileMakeDir.js')
let FileTruncate = require('./FileTruncate.js')
let FileRename = require('./FileRename.js')
let ParamPush = require('./ParamPush.js')
let FileClose = require('./FileClose.js')
let CommandTriggerControl = require('./CommandTriggerControl.js')
let CommandInt = require('./CommandInt.js')
let CommandTOL = require('./CommandTOL.js')
let FileRemoveDir = require('./FileRemoveDir.js')
let CommandVtolTransition = require('./CommandVtolTransition.js')
let LogRequestData = require('./LogRequestData.js')
let ParamGet = require('./ParamGet.js')
let CommandLong = require('./CommandLong.js')
let MessageInterval = require('./MessageInterval.js')
let WaypointPull = require('./WaypointPull.js')
let CommandBool = require('./CommandBool.js')
let FileRead = require('./FileRead.js')
let SetMavFrame = require('./SetMavFrame.js')
let CommandHome = require('./CommandHome.js')
let VehicleInfoGet = require('./VehicleInfoGet.js')
let FileChecksum = require('./FileChecksum.js')
let LogRequestList = require('./LogRequestList.js')
let ParamPull = require('./ParamPull.js')
let StreamRate = require('./StreamRate.js')
let CommandTriggerInterval = require('./CommandTriggerInterval.js')

module.exports = {
  WaypointPush: WaypointPush,
  WaypointSetCurrent: WaypointSetCurrent,
  ParamSet: ParamSet,
  LogRequestEnd: LogRequestEnd,
  FileList: FileList,
  FileRemove: FileRemove,
  FileOpen: FileOpen,
  MountConfigure: MountConfigure,
  SetMode: SetMode,
  WaypointClear: WaypointClear,
  FileWrite: FileWrite,
  FileMakeDir: FileMakeDir,
  FileTruncate: FileTruncate,
  FileRename: FileRename,
  ParamPush: ParamPush,
  FileClose: FileClose,
  CommandTriggerControl: CommandTriggerControl,
  CommandInt: CommandInt,
  CommandTOL: CommandTOL,
  FileRemoveDir: FileRemoveDir,
  CommandVtolTransition: CommandVtolTransition,
  LogRequestData: LogRequestData,
  ParamGet: ParamGet,
  CommandLong: CommandLong,
  MessageInterval: MessageInterval,
  WaypointPull: WaypointPull,
  CommandBool: CommandBool,
  FileRead: FileRead,
  SetMavFrame: SetMavFrame,
  CommandHome: CommandHome,
  VehicleInfoGet: VehicleInfoGet,
  FileChecksum: FileChecksum,
  LogRequestList: LogRequestList,
  ParamPull: ParamPull,
  StreamRate: StreamRate,
  CommandTriggerInterval: CommandTriggerInterval,
};
