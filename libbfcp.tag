<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>bfcp_floor_list.c</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpsrv/</path>
    <filename>de/d05/bfcp__floor__list_8c</filename>
    <includes id="d3/dbd/bfcp__floor__list_8h" name="bfcp_floor_list.h" local="yes" imported="no">bfcp_floor_list.h</includes>
    <member kind="function">
      <type>struct bfcp_list_floors *</type>
      <name>bfcp_create_floor_list</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>ab06a2835f323fdc462f8f6aef892bc67</anchor>
      <arglist>(UINT16 Max_Num)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_insert_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>adcea734c49e78c653b48f56eea6bd57c</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID, UINT16 chairID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_return_number_floors</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>aba7087a180104060b94284c4c811a6ee</anchor>
      <arglist>(bfcp_list_floors *lfloors)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_change_number_floors</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>ab017ac41127be0d921dbb761ce25ed73</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 Num)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_exist_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>acd229d62a0fff88748b97306a791e1e7</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_delete_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>a4844d005a53a5b955c87edb4fcd85131</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_change_chair</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>a1111b6324ee5187d734623163d599cac</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID, UINT16 chairID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_return_number_granted_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>a94ac2f97c78590b14eabfe2e70075bf1</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_change_number_granted_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>a6c4449c95df5bfeb91021fbdcb860843</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID, UINT16 limit_granted_floor)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_change_state_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>a17dd909b231f24d749eb2b7a527ffc22</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID, e_floor_state state)</arglist>
    </member>
    <member kind="function">
      <type>e_floor_state</type>
      <name>bfcp_return_state_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>ab3bd61848851847207848f407636ce2e</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_return_position_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>a4d50592bdce0d7f56c382365a1c56d0d</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>bfcp_return_chair_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>a6cf0ce894451c660248c7cfcbac4e3b3</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_exist_user_as_a_chair</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>aa8ea6d4308745755a92949fec6e854cb</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 chairID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_clean_floor_list</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>af503a0617b3a79cd385e1ef590ac818d</anchor>
      <arglist>(bfcp_list_floors *lfloors)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_remove_floor_list</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>a7138b0d857b8c6e3bd5b98e4f305b8d8</anchor>
      <arglist>(bfcp_list_floors **lfloorsp)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>remove_request_from_the_floor</name>
      <anchorfile>de/d05/bfcp__floor__list_8c.html</anchorfile>
      <anchor>a636b3aacd80b943d1072f3703c509e07</anchor>
      <arglist>(bfcp_floors *floors, UINT16 userID)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_floor_list.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpsrv/</path>
    <filename>d3/dbd/bfcp__floor__list_8h</filename>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <class kind="struct">floor_query</class>
    <class kind="struct">bfcp_floors</class>
    <class kind="struct">bfcp_list_floors</class>
    <member kind="typedef">
      <type>enum floor_state</type>
      <name>e_floor_state</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>aabbd0bfeb7476793f2032bd3cb8a3579</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct floor_query</type>
      <name>floor_query</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a2daf5ad0fc68bf8777b8f13d3894c676</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_floors</type>
      <name>bfcp_floors</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a13c218804a93c839acda1a7efba8cb5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bfcp_floors *</type>
      <name>floors</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>ae1b1242f8ef1e0e7e9f3d3003031e3b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_list_floors</type>
      <name>bfcp_list_floors</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>ae44e7d789e067d17dd42f7424037bf7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bfcp_list_floors *</type>
      <name>lfloors</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a29570d3aedb0041d4f2951311089f5f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>floor_state</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>af2e42763072e6bc973ada090373eb764</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_FLOOR_STATE_WAITING</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>af2e42763072e6bc973ada090373eb764a6b4cbc7ae5e0c9bc4b033a163be3f4a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_FLOOR_STATE_ACCEPTED</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>af2e42763072e6bc973ada090373eb764a5bc4007ad97878c7fda401e37ab6d34a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_FLOOR_STATE_GRANTED</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>af2e42763072e6bc973ada090373eb764a1b224c9c9aaef83f365e96dee0d51b56</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>struct bfcp_list_floors *</type>
      <name>bfcp_create_floor_list</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>ab06a2835f323fdc462f8f6aef892bc67</anchor>
      <arglist>(UINT16 Max_Num)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_insert_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>adcea734c49e78c653b48f56eea6bd57c</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID, UINT16 chairID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_return_number_floors</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>aba7087a180104060b94284c4c811a6ee</anchor>
      <arglist>(bfcp_list_floors *lfloors)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_change_number_floors</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>ab017ac41127be0d921dbb761ce25ed73</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 Num)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_exist_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>acd229d62a0fff88748b97306a791e1e7</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_delete_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a4844d005a53a5b955c87edb4fcd85131</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_change_chair</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a1111b6324ee5187d734623163d599cac</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID, UINT16 chairID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_return_number_granted_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a94ac2f97c78590b14eabfe2e70075bf1</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_change_number_granted_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a6c4449c95df5bfeb91021fbdcb860843</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID, UINT16 limit_granted_floor)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_change_state_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a17dd909b231f24d749eb2b7a527ffc22</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID, e_floor_state state)</arglist>
    </member>
    <member kind="function">
      <type>e_floor_state</type>
      <name>bfcp_return_state_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>ab3bd61848851847207848f407636ce2e</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_return_position_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a4d50592bdce0d7f56c382365a1c56d0d</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>bfcp_return_chair_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a6cf0ce894451c660248c7cfcbac4e3b3</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_exist_user_as_a_chair</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>aa8ea6d4308745755a92949fec6e854cb</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 chairID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_clean_floor_list</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>af503a0617b3a79cd385e1ef590ac818d</anchor>
      <arglist>(bfcp_list_floors *lfloors)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_remove_floor_list</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a7138b0d857b8c6e3bd5b98e4f305b8d8</anchor>
      <arglist>(bfcp_list_floors **lfloorsp)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>remove_request_from_the_floor</name>
      <anchorfile>d3/dbd/bfcp__floor__list_8h.html</anchorfile>
      <anchor>a636b3aacd80b943d1072f3703c509e07</anchor>
      <arglist>(bfcp_floors *floors, UINT16 userID)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>BFCP_fsm.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d3/d7d/BFCP__fsm_8cpp</filename>
    <includes id="db/d06/stdafx_8h" name="stdafx.h" local="yes" imported="no">stdafx.h</includes>
    <includes id="d7/d66/BFCP__fsm_8h" name="BFCP_fsm.h" local="yes" imported="no">BFCP_fsm.h</includes>
  </compound>
  <compound kind="file">
    <name>BFCP_fsm.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d7/d66/BFCP__fsm_8h</filename>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <includes id="da/dc7/bfcp__strings_8h" name="bfcp_strings.h" local="yes" imported="no">bfcp_strings.h</includes>
    <class kind="class">BFCP_fsm</class>
    <class kind="struct">BFCP_fsm::st_BFCP_fsm</class>
    <class kind="struct">BFCP_fsm::st_BFCP_fsm_event</class>
    <class kind="struct">_bfcp_actions</class>
    <member kind="function">
      <type>__inline const char *</type>
      <name>getBfcpFsmAct</name>
      <anchorfile>d7/d66/BFCP__fsm_8h.html</anchorfile>
      <anchor>a8f9d2e2c850303b0cb98b706e9579ce2</anchor>
      <arglist>(UINT32 p)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static struct _bfcp_actions</type>
      <name>_bfcp_action</name>
      <anchorfile>d7/d66/BFCP__fsm_8h.html</anchorfile>
      <anchor>ae538a7fb0e22b05f37cc29262f94ba80</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_link_list.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpsrv/</path>
    <filename>de/d2a/bfcp__link__list_8cpp</filename>
    <includes id="db/d06/stdafx_8h" name="stdafx.h" local="yes" imported="no">stdafx.h</includes>
    <includes id="de/def/bfcp__threads_8h" name="bfcp_threads.h" local="yes" imported="no">bfcp_threads.h</includes>
    <includes id="d4/dd6/BFCPexception_8h" name="BFCPexception.h" local="yes" imported="no">BFCPexception.h</includes>
    <includes id="d6/d95/bfcp__link__list_8h" name="bfcp_link_list.h" local="yes" imported="no">bfcp_link_list.h</includes>
  </compound>
  <compound kind="file">
    <name>bfcp_link_list.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpsrv/</path>
    <filename>d6/d95/bfcp__link__list_8h</filename>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <includes id="d3/dbd/bfcp__floor__list_8h" name="bfcp_floor_list.h" local="yes" imported="no">bfcp_floor_list.h</includes>
    <includes id="d3/d20/bfcp__user__list_8h" name="bfcp_user_list.h" local="yes" imported="no">bfcp_user_list.h</includes>
    <includes id="de/def/bfcp__threads_8h" name="bfcp_threads.h" local="yes" imported="no">bfcp_threads.h</includes>
    <class kind="struct">floor_request_query</class>
    <class kind="struct">bfcp_floor</class>
    <class kind="struct">bfcp_node</class>
    <class kind="struct">bfcp_queue</class>
    <class kind="class">BFCP_LinkList</class>
    <member kind="typedef">
      <type>struct floor_request_query</type>
      <name>floor_request_query</name>
      <anchorfile>d6/d95/bfcp__link__list_8h.html</anchorfile>
      <anchor>a19c5d1e7deec35e86c8cda05ed594e17</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_floor</type>
      <name>bfcp_floor</name>
      <anchorfile>d6/d95/bfcp__link__list_8h.html</anchorfile>
      <anchor>aff4fafcd525a40b00c12962315510db1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bfcp_floor *</type>
      <name>pfloor</name>
      <anchorfile>d6/d95/bfcp__link__list_8h.html</anchorfile>
      <anchor>a89b044ba72e44c9693aa1d2486695e1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_node</type>
      <name>bfcp_node</name>
      <anchorfile>d6/d95/bfcp__link__list_8h.html</anchorfile>
      <anchor>a87cc7408a03f12e95c3bb4b0deb2c8ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bfcp_node *</type>
      <name>pnode</name>
      <anchorfile>d6/d95/bfcp__link__list_8h.html</anchorfile>
      <anchor>a262ce6d2ef10332bacbfb8c112eb1f23</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_queue</type>
      <name>bfcp_queue</name>
      <anchorfile>d6/d95/bfcp__link__list_8h.html</anchorfile>
      <anchor>a5f26e219df9bf0a7c7d284ba0672668c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_messages.c</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpmsg/</path>
    <filename>d3/d7c/bfcp__messages_8c</filename>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <member kind="function">
      <type>void</type>
      <name>BFCP_msg_LogCallback</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a8e70dea7e664db80d7b1496227c9452f</anchor>
      <arglist>(tLog_callback trace_function)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DumpBfcpBuff</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a580fed48224442407d56d5034185af38</anchor>
      <arglist>(char *txt, unsigned char *dp, int sz)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BFCP_msgLog</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a5a4d8d1e9a6d60ef737c632443f3585f</anchor>
      <arglist>(char *pcFile, int iLine, int iErrLevel, char *pcFormat,...)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_arguments *</type>
      <name>bfcp_new_arguments</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>aaea577a165adc21e37d6f4f19f51ef61</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_arguments</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a510113b4f894a64a08d8f2c34d71cd5e</anchor>
      <arglist>(bfcp_arguments *arguments)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_new_message</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a48d957ca0a49f0b018e0f9cee35414bf</anchor>
      <arglist>(unsigned char *buffer, UINT16 length)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_copy_message</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>aa98625cdc6a8043021e24c2bd16e6c14</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_message</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>ae0b45ea592d5404e3ce0ecd4409ccdd9</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_entity *</type>
      <name>bfcp_new_entity</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a7f3e0219c91e385fc06d25d819527ceb</anchor>
      <arglist>(UINT32 conferenceID, UINT16 transactionID, UINT16 userID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_entity</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>ae4e117079435e389d3a436e34b530a08</anchor>
      <arglist>(bfcp_entity *entity)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_id_list *</type>
      <name>bfcp_new_floor_id_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a934370fecb84034abebb66b28e8119d5</anchor>
      <arglist>(UINT16 fID,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_add_floor_id_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a35834707ab8b28b25ac876a3b0e9d91e</anchor>
      <arglist>(bfcp_floor_id_list *list, UINT16 fID,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_floor_id_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a90c80028ee919a5b42a4894c5b4106f4</anchor>
      <arglist>(bfcp_floor_id_list *list)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_supported_list *</type>
      <name>bfcp_new_supported_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>aa47a84985a0be4591453e55d05533388</anchor>
      <arglist>(UINT8 element,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_supported_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a221d1ccc68135d6410211dca13aa001f</anchor>
      <arglist>(bfcp_supported_list *list)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_request_status *</type>
      <name>bfcp_new_request_status</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a95dc785bc343502c0708332164798c6c</anchor>
      <arglist>(UINT16 rs, UINT16 qp)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_request_status</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a5c29d9ede9f94cb0cf501292b9066640</anchor>
      <arglist>(bfcp_request_status *request_status)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_error *</type>
      <name>bfcp_new_error</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a25b40e9c1501c0036c10913575c6d9df</anchor>
      <arglist>(e_bfcp_error_codes code, bfcp_unknown_m_error_details *details)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_error</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a5037cb308f81843e28ded8fb34180206</anchor>
      <arglist>(bfcp_error *error)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_unknown_m_error_details *</type>
      <name>bfcp_new_unknown_m_error_details_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a0a1db202f529f7104288f52b4aabd51c</anchor>
      <arglist>(UINT16 attribute,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_add_unknown_m_error_details_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a94f1312c12e24ede1f884fc5cd2a6b0b</anchor>
      <arglist>(bfcp_unknown_m_error_details *list, UINT16 attribute,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_unknown_m_error_details_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a062fb6bb15f2d8fc59a1ffa37e5af957</anchor>
      <arglist>(bfcp_unknown_m_error_details *details)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_user_information *</type>
      <name>bfcp_new_user_information</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a4e6c0c4ebc191673cbca2fdf2eaf80e1</anchor>
      <arglist>(UINT16 ID, char *display, char *uri)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_user_information</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a11b10f6d5c8e2bb9470798d94ffd6d58</anchor>
      <arglist>(bfcp_user_information *info)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_request_information *</type>
      <name>bfcp_new_floor_request_information</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a90c1d4886cc09c87b92a4652894b18ff</anchor>
      <arglist>(UINT16 frqID, bfcp_overall_request_status *oRS, bfcp_floor_request_status *fRS, bfcp_user_information *beneficiary, bfcp_user_information *requested_by, e_bfcp_priority priority, char *pInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_list_floor_request_information</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a96d34688fcdb37a6a195fc8b4a4b1f89</anchor>
      <arglist>(bfcp_floor_request_information *frqInfo,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_add_floor_request_information_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a3fee13b7a25922b0af1b07e3fea8f2ec</anchor>
      <arglist>(bfcp_floor_request_information *list,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_floor_request_information_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a56b124acd8455c3eaebba1cf024f5e4b</anchor>
      <arglist>(bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_request_status *</type>
      <name>bfcp_new_floor_request_status</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a52a2bba6c2badbf15e50dae592161c1a</anchor>
      <arglist>(UINT16 fID, UINT16 rs, UINT16 qp, char *sInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_list_floor_request_status</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a6dad90071ddea0e96d0592417fe17304</anchor>
      <arglist>(bfcp_floor_request_status *fRS,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_add_floor_request_status_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a83c246d0d7839d87f26deef776840b7a</anchor>
      <arglist>(bfcp_floor_request_status *list,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_floor_request_status_list</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>ab892deb58d334de99624145a71d2768b</anchor>
      <arglist>(bfcp_floor_request_status *floor_request_status)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_overall_request_status *</type>
      <name>bfcp_new_overall_request_status</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a38d37aba5688be79ad3918a628b6c60e</anchor>
      <arglist>(UINT16 frqID, UINT16 rs, UINT16 qp, char *sInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_overall_request_status</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>ab4c88bd809d292862949f466e56c0b97</anchor>
      <arglist>(bfcp_overall_request_status *overall_request_status)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_digest *</type>
      <name>bfcp_new_digest</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a2f6ccef3908a10c4737a080467bfdbbc</anchor>
      <arglist>(UINT16 algorithm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_digest</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>a56ba11df2a21a5dbed006428eab1f89f</anchor>
      <arglist>(bfcp_digest *digest)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static tLog_callback</type>
      <name>_Log_callback</name>
      <anchorfile>d3/d7c/bfcp__messages_8c.html</anchorfile>
      <anchor>aacdd9dc72e2754c67bf253c89e9b6f4c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_messages.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpmsg/</path>
    <filename>d8/d2b/bfcp__messages_8h</filename>
    <class kind="struct">s_bfcp_msg_event</class>
    <class kind="struct">bfcp_message</class>
    <class kind="struct">bfcp_entity</class>
    <class kind="struct">bfcp_floor_id_list</class>
    <class kind="struct">bfcp_supported_list</class>
    <class kind="struct">bfcp_request_status</class>
    <class kind="struct">bfcp_unknown_m_error_details</class>
    <class kind="struct">bfcp_error</class>
    <class kind="struct">bfcp_user_information</class>
    <class kind="struct">bfcp_floor_request_status</class>
    <class kind="struct">bfcp_overall_request_status</class>
    <class kind="struct">bfcp_floor_request_information</class>
    <class kind="struct">bfcp_digest</class>
    <class kind="struct">bfcp_arguments</class>
    <class kind="struct">bfcp_received_attribute</class>
    <class kind="struct">bfcp_received_message</class>
    <class kind="struct">bfcp_received_message_error</class>
    <member kind="define">
      <type>#define</type>
      <name>INT8</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a7e125472d65b57f10905accbed140b99</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT8</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ad8ce12d83f204245685f98caf9d03944</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT16</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>abc743ce126c3ada10501baffb3ca2295</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT16</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab1922c2d8643eb7da964d427604e992e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT32</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aac92c5ec332dafe0abb24688dad1b795</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT32</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a69afa2e50b905f4eab1f2df8a3fd9f23</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT64</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a8606fb1d53339b43e7417d2f96db025f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT64</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a3a206425f9cab93c58d2981b5624e304</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INF</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a12c2040f25d8e3a7b9e1c2024c618cb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WAR</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a9423380a92639b296ea0a984ea7e1c6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERR</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a735563036dced0b7d6cc98f97ea4978b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_SOCKET</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a7a290f9fa469b1059476e0fd3edcf89f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INVALID_SOCKET</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a26769957ec1a2beaf223f33b66ee64ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ft_tcsncpy</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a8f708317c91bcc5256344d82c8ac4527</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_T</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae936e4c15227768f7da4e0951def89c8</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_MAX_ALLOWED_SIZE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0c7f607df14955dc805d80574d5a006b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_MAX_RG</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a4db65da17b6460fda021c94fd8311eca</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_STRING_SIZE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>afcee5da2ad8027897087d97e3d991e6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>tLog_callback</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>abfaa0143f4723b8369e919bbe995d713</anchor>
      <arglist>)(char *pcFile, int iLine, int iErrLevel, char *pcFormat,...)</arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_message</type>
      <name>bfcp_message</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a908c5fd4d7c85416ce3d47285996ff5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_entity</type>
      <name>bfcp_entity</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a18e0c34467c2d89a08f9b9ea3169b495</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_floor_id_list</type>
      <name>bfcp_floor_id_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ac8616b4706389124d58919371550ae6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_supported_list</type>
      <name>bfcp_supported_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a726cab654da4aee0ceb066296170ecdb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_request_status</type>
      <name>bfcp_request_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a69ed51c2d89b01e2becfca8f7ba2d2ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_unknown_m_error_details</type>
      <name>bfcp_unknown_m_error_details</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a99bbc6fe854c930ef90bc7584a20c74e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_error</type>
      <name>bfcp_error</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a64a1c3a5b4f5378db91a377b9d03e26b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_user_information</type>
      <name>bfcp_user_information</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aed054ac096286aec7850c9e7e34b0a09</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_floor_request_status</type>
      <name>bfcp_floor_request_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>af744c18260a8eff35f9c1a49b4445dbd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_overall_request_status</type>
      <name>bfcp_overall_request_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a1547b7b06ef039c5e5505794765fcd30</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_floor_request_information</type>
      <name>bfcp_floor_request_information</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aecc181d97f77156a0189d5ba1813927b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_digest</type>
      <name>bfcp_digest</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ad48a70c536aa86963616d5ca96a662ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_arguments</type>
      <name>bfcp_arguments</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a99332a37a31963fc18051febf1eff840</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_received_attribute</type>
      <name>bfcp_received_attribute</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a1c753ad7cc1e965eaa297dd7e7b9e7c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_received_message</type>
      <name>bfcp_received_message</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a4226534f86e2565b4ffb5e0d3d928f51</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_received_message_error</type>
      <name>bfcp_received_message_error</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ad4c09b24aad406f30edf930322dbc42f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>e_bfcp_primitives</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>InvalidPrimitive</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6baedc7c073021764317741d8a06cc74c71</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FloorRequest</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6bac7fd3ff350a96aa6fe31bda0d042ba42</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FloorRelease</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6ba69834e3e30a979519addf60d01664da7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FloorRequestQuery</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6bab7e0df0f1f53ff445a7c0fc418ea2dc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FloorRequestStatus</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6ba8b463f821bc9e2614e881a426394445c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>UserQuery</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6bae8b22709f4478a7db9eedcff9a69c65e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>UserStatus</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6bae6e9748791eaeeb41a94f1f8e34fdfc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FloorQuery</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6bafa029ff7c525c9ec33d19e0f8e025c29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FloorStatus</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6baf38d9606d6b35040a8e3d7f1fb1a8250</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ChairAction</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6bae838a32d589df9bf9faa28027ec80315</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ChairActionAck</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6bacde6d3aa2f4fb1030bee9d497305a995</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Hello</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6ba81fd637bf30ec1aeef591f5788112963</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>HelloAck</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6ba22eaf9ddf535c19a3b49c5e98f479e96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Error</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a280397c2033baf901f495799be195c6ba4dfd42ec49d09d8c6555c218301cc30f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>e_bfcp_attibutes</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INVALID_ATTRIBUTE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55ac331111ea9904f73785a64ed9eb9c988</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BENEFICIARY_ID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a35f641d6f73f2714fdfc29aed98f79a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOR_ID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a1ff30cee18d2814c728104d8c2aee22d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOR_REQUEST_ID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a3ab0637701e7b9c2b17c668bb87da05e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PRIORITY</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a117d4e929adf16e40bd27b3e7c7cee51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REQUEST_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a884a2143dcb65446f013d9412db59623</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ERROR_CODE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55af92feceab1e86b1db3922220d4e26664</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ERROR_INFO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a2a25ff6de8725c46f15856aec63fcbc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PARTICIPANT_PROVIDED_INFO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a481de4e38e1850846986c9372de6d773</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STATUS_INFO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55af6765dc35443d7fbb2d12a6192c0f5ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SUPPORTED_ATTRIBUTES</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a962c337ae3e64425dea8aed7f7cc3710</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SUPPORTED_PRIMITIVES</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a91c02f74addf03bf7fb3ab8e5ab29a6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>USER_DISPLAY_NAME</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a83469d631a634d4b5ce70b7bc7310199</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>USER_URI</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a40e7e5bb0938d0f690e248ae6ec32000</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BENEFICIARY_INFORMATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a068267d36e20c6531a3d13e558082eea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOR_REQUEST_INFORMATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a76cc0eb756d4f04756ae1ed0411bc6f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REQUESTED_BY_INFORMATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55abaff9a805013ae503ad11671fd3618f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOR_REQUEST_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55a8bdd7fa5542ba18c3f43d8d71a263abf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OVERALL_REQUEST_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55ac1fbe1056eca2a624e440ce6257455a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NONCE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55ae792e90f68de1ea122e7af10c01cc276</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DIGEST</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5b004d78fb74b5efc684d0ac8bf2ee55ab41e83ee2c6e23b86b996ea3f8cd3aee</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>e_bfcp_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae97c8a1d09b0434ad3f6956a15991fde</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_INVALID_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae97c8a1d09b0434ad3f6956a15991fdea0ae1bb55fb01f17e57bf1a021cdeb745</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_PENDING</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae97c8a1d09b0434ad3f6956a15991fdead8ecaeb3c80ba14b1f8ec12f5d936f8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACCEPTED</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae97c8a1d09b0434ad3f6956a15991fdea1c50cc9810d129ac38fba0e5e7667070</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_GRANTED</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae97c8a1d09b0434ad3f6956a15991fdeac23d9e8eb31b6775902a755239bb80b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_DENIED</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae97c8a1d09b0434ad3f6956a15991fdeaf7679b79f235f066fed11be27bb9824a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_CANCELLED</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae97c8a1d09b0434ad3f6956a15991fdeaa6e90f68067b955d9f6cd81ca490aa0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_RELEASED</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae97c8a1d09b0434ad3f6956a15991fdea64536b7409875caa3fba121e8f0a83db</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_REVOKED</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae97c8a1d09b0434ad3f6956a15991fdea917305ac0ca9b9e131b9470531a8cf65</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>e_bfcp_priority</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab76caa18a51fd7383df2ac9735b76204</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_LOWEST_PRIORITY</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab76caa18a51fd7383df2ac9735b76204a1f60507146ef82176a7aaa9e3ccec6c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_LOW_PRIORITY</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab76caa18a51fd7383df2ac9735b76204ab13764617e5ba516f6634feef7a69a6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_NORMAL_PRIORITY</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab76caa18a51fd7383df2ac9735b76204a096a43084b58da166b187a5618dcdf28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_HIGH_PRIORITY</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab76caa18a51fd7383df2ac9735b76204af2cf0835f7b9407128adbc585e99dac1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_HIGHEST_PRIORITY</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab76caa18a51fd7383df2ac9735b76204a0f8db57dbe57f6d48cb1403983b7a208</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>e_bfcp_error_codes</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_INVALID_ERROR_CODES</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664a84a6a68b9c74f05dceb9ec8951c2a9e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_CONFERENCE_DOES_NOT_EXIST</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664a8e91e70e489430f24305242710365033</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_USER_DOES_NOT_EXIST</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664aab34ecd278b30b1d5f44e1ea373d5c64</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_UNKNOWN_PRIMITIVE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664a179878cec98285f21b8684b36ce65b12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_UNKNOWN_MANDATORY_ATTRIBUTE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664aa00ac87845967f3529e39dd280fc23f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_UNAUTHORIZED_OPERATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664a8fe1eeec2234b9eb5ee58019aa1c8b61</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_INVALID_FLOORID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664a81c7c20a69280e888243d00660b02627</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_FLOORREQUEST_DOES_NOT_EXIST</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664afc70e64fddab1c07d69f5f21e583d3c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_MAX_FLOORREQUESTS_REACHED</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664a8503f8a7121a443dfbb2209f3a355909</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_USE_TLS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664aeed27fe97299058196c795c83c7fdf55</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_DIGEST_ATTRIBUTE_REQUIRED</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664a8671a72f77f720c613b09a7681702f69</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_INVALID_NONCE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664acc73a74cd8df6ca1459537f603c56aea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_AUTHENTICATION_FAILED</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02fd38109dc2452190dcfed90017d664ae7aea261028415485f899ec5faf76688</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>e_bfcp_specific_error_codes</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0f22a94c69e33e342e26b1abd6b15140</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_INVALID_SPECIFIC_ERROR_CODES</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0f22a94c69e33e342e26b1abd6b15140ad780d0f7f296ff9bb3d2e2471040ddcb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_WRONG_VERSION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0f22a94c69e33e342e26b1abd6b15140a3663305a54c16f2527b64ab2d05ab0b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_RESERVED_NOT_ZERO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0f22a94c69e33e342e26b1abd6b15140a132aacee669d7f0a0e511174818e9d5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_UNKNOWN_ATTRIBUTE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0f22a94c69e33e342e26b1abd6b15140ae3f379578d9b5d084cbfa8574c5c3c20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_WRONG_LENGTH</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0f22a94c69e33e342e26b1abd6b15140ac8f6cef7dca6223e35bd520ba2e37353</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_PARSING_ERROR</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0f22a94c69e33e342e26b1abd6b15140a7d194c3beceb9cd978ac6d5bef4c3802</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BFCP_msg_LogCallback</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a8e70dea7e664db80d7b1496227c9452f</anchor>
      <arglist>(tLog_callback trace_function)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BFCP_msgLog</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5a4d8d1e9a6d60ef737c632443f3585f</anchor>
      <arglist>(char *pcFile, int iLine, int iErrLevel, char *pcFormat,...)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DumpBfcpBuff</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a580fed48224442407d56d5034185af38</anchor>
      <arglist>(char *txt, unsigned char *dp, int sz)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_arguments *</type>
      <name>bfcp_new_arguments</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aaea577a165adc21e37d6f4f19f51ef61</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_arguments</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a510113b4f894a64a08d8f2c34d71cd5e</anchor>
      <arglist>(bfcp_arguments *arguments)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_new_message</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a48d957ca0a49f0b018e0f9cee35414bf</anchor>
      <arglist>(unsigned char *buffer, UINT16 length)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_copy_message</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aa98625cdc6a8043021e24c2bd16e6c14</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_message</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae0b45ea592d5404e3ce0ecd4409ccdd9</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_entity *</type>
      <name>bfcp_new_entity</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a7f3e0219c91e385fc06d25d819527ceb</anchor>
      <arglist>(UINT32 conferenceID, UINT16 transactionID, UINT16 userID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_entity</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae4e117079435e389d3a436e34b530a08</anchor>
      <arglist>(bfcp_entity *entity)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_id_list *</type>
      <name>bfcp_new_floor_id_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a934370fecb84034abebb66b28e8119d5</anchor>
      <arglist>(UINT16 fID,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_add_floor_id_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a35834707ab8b28b25ac876a3b0e9d91e</anchor>
      <arglist>(bfcp_floor_id_list *list, UINT16 fID,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_floor_id_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a90c80028ee919a5b42a4894c5b4106f4</anchor>
      <arglist>(bfcp_floor_id_list *list)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_supported_list *</type>
      <name>bfcp_new_supported_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aa47a84985a0be4591453e55d05533388</anchor>
      <arglist>(UINT8 element,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_supported_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a221d1ccc68135d6410211dca13aa001f</anchor>
      <arglist>(bfcp_supported_list *list)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_request_status *</type>
      <name>bfcp_new_request_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a95dc785bc343502c0708332164798c6c</anchor>
      <arglist>(UINT16 rs, UINT16 qp)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_request_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5c29d9ede9f94cb0cf501292b9066640</anchor>
      <arglist>(bfcp_request_status *request_status)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_error *</type>
      <name>bfcp_new_error</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a25b40e9c1501c0036c10913575c6d9df</anchor>
      <arglist>(e_bfcp_error_codes code, bfcp_unknown_m_error_details *details)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_error</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a5037cb308f81843e28ded8fb34180206</anchor>
      <arglist>(bfcp_error *error)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_unknown_m_error_details *</type>
      <name>bfcp_new_unknown_m_error_details_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0a1db202f529f7104288f52b4aabd51c</anchor>
      <arglist>(UINT16 attribute,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_add_unknown_m_error_details_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a94f1312c12e24ede1f884fc5cd2a6b0b</anchor>
      <arglist>(bfcp_unknown_m_error_details *list, UINT16 attribute,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_unknown_m_error_details_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a062fb6bb15f2d8fc59a1ffa37e5af957</anchor>
      <arglist>(bfcp_unknown_m_error_details *details)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_user_information *</type>
      <name>bfcp_new_user_information</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a4e6c0c4ebc191673cbca2fdf2eaf80e1</anchor>
      <arglist>(UINT16 ID, char *display, char *uri)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_user_information</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a11b10f6d5c8e2bb9470798d94ffd6d58</anchor>
      <arglist>(bfcp_user_information *info)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_request_information *</type>
      <name>bfcp_new_floor_request_information</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a90c1d4886cc09c87b92a4652894b18ff</anchor>
      <arglist>(UINT16 frqID, bfcp_overall_request_status *oRS, bfcp_floor_request_status *fRS, bfcp_user_information *beneficiary, bfcp_user_information *requested_by, e_bfcp_priority priority, char *pInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_list_floor_request_information</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a96d34688fcdb37a6a195fc8b4a4b1f89</anchor>
      <arglist>(bfcp_floor_request_information *frqInfo,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_add_floor_request_information_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a3fee13b7a25922b0af1b07e3fea8f2ec</anchor>
      <arglist>(bfcp_floor_request_information *list,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_floor_request_information_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a56b124acd8455c3eaebba1cf024f5e4b</anchor>
      <arglist>(bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_request_status *</type>
      <name>bfcp_new_floor_request_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a52a2bba6c2badbf15e50dae592161c1a</anchor>
      <arglist>(UINT16 fID, UINT16 rs, UINT16 qp, char *sInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_list_floor_request_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a6dad90071ddea0e96d0592417fe17304</anchor>
      <arglist>(bfcp_floor_request_status *fRS,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_add_floor_request_status_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a83c246d0d7839d87f26deef776840b7a</anchor>
      <arglist>(bfcp_floor_request_status *list,...)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_floor_request_status_list</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab892deb58d334de99624145a71d2768b</anchor>
      <arglist>(bfcp_floor_request_status *floor_request_status)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_overall_request_status *</type>
      <name>bfcp_new_overall_request_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a38d37aba5688be79ad3918a628b6c60e</anchor>
      <arglist>(UINT16 frqID, UINT16 rs, UINT16 qp, char *sInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_overall_request_status</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab4c88bd809d292862949f466e56c0b97</anchor>
      <arglist>(bfcp_overall_request_status *overall_request_status)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_digest *</type>
      <name>bfcp_new_digest</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a2f6ccef3908a10c4737a080467bfdbbc</anchor>
      <arglist>(UINT16 algorithm)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_digest</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a56ba11df2a21a5dbed006428eab1f89f</anchor>
      <arglist>(bfcp_digest *digest)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae053c5cf8237485239f8decf6420130c</anchor>
      <arglist>(bfcp_arguments *arguments)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>bfcp_build_commonheader</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a89ee55267abfe3e80e63d8af63eac301</anchor>
      <arglist>(bfcp_message *message, bfcp_entity *entity, e_bfcp_primitives primitive)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>bfcp_build_attribute_tlv</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a1463c075c4fceb97d0111f4541ee16c0</anchor>
      <arglist>(bfcp_message *message, UINT16 position, UINT16 type, UINT16 mandatory_bit, UINT16 length)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorRequest</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a1f199ef839c341efce1920f7f56452cc</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_id_list *fID, UINT16 bID, char *pInfo, e_bfcp_priority priority)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorRelease</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>adec6c394f957aaad50842c34190eb8f4</anchor>
      <arglist>(bfcp_entity *entity, UINT16 frqID)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorRequestQuery</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0ecb176f32978b2936e01853806bc32e</anchor>
      <arglist>(bfcp_entity *entity, UINT16 frqID)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorRequestStatus</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a4493665b5fd1fc32f24b5bf698cce1f9</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_UserQuery</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ad3cb1908446b3366aa0beec4dee8d94e</anchor>
      <arglist>(bfcp_entity *entity, UINT16 bID)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_UserStatus</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab69a380c46b8ff7eb39f12e26891edd1</anchor>
      <arglist>(bfcp_entity *entity, bfcp_user_information *beneficiary, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorQuery</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>adac814913ed8a8c0117cdebdf38c0f69</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_id_list *fID)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorStatus</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae9acad985d3d8f348a4747b69875e172</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_id_list *fID, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_ChairAction</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae670a7d44d8ca6bca21fd19a1cc739f2</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_ChairActionAck</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a8e94272e1fa23b90a5a22ecfe4bf3bf8</anchor>
      <arglist>(bfcp_entity *entity)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_Hello</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a74ad9a9ad8bc4387fcb1ee10f2bba694</anchor>
      <arglist>(bfcp_entity *entity)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_HelloAck</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a4dc220a40f33e2123d317b49410d3302</anchor>
      <arglist>(bfcp_entity *entity, bfcp_supported_list *primitives, bfcp_supported_list *attributes)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_Error</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aa19d19fcc7cade3e1135d47f436ba978</anchor>
      <arglist>(bfcp_entity *entity, bfcp_error *error, char *eInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_BENEFICIARY_ID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a36cf3f37035eb23b1c6c34fd395b44ec</anchor>
      <arglist>(bfcp_message *message, UINT16 bID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_FLOOR_ID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a13727ccc865967350a596bcf9e79fdf6</anchor>
      <arglist>(bfcp_message *message, UINT16 fID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_FLOOR_REQUEST_ID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a39aa271f51960734f1f4752253d3b21d</anchor>
      <arglist>(bfcp_message *message, UINT16 frqID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_PRIORITY</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a651a9b891605a29c2afac2649aca5cdc</anchor>
      <arglist>(bfcp_message *message, e_bfcp_priority priority)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_REQUEST_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0d6cf216b01f4ddda23083dfd00b50b6</anchor>
      <arglist>(bfcp_message *message, bfcp_request_status *rs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_ERROR_CODE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a4a421b3d2dbe6872efe812591de7d2fc</anchor>
      <arglist>(bfcp_message *message, bfcp_error *error)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_ERROR_INFO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a8a3ebb6ba56055cc005cdd827615329c</anchor>
      <arglist>(bfcp_message *message, char *eInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_PARTICIPANT_PROVIDED_INFO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a1bd53d9f1f0c5c4d05882af0d87e2a0c</anchor>
      <arglist>(bfcp_message *message, char *pInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_STATUS_INFO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>adec2a8fe6e2cc9a0857bd13d429d8ecb</anchor>
      <arglist>(bfcp_message *message, char *sInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_SUPPORTED_ATTRIBUTES</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a8f4930b053213d4b6f8636bfcef59d44</anchor>
      <arglist>(bfcp_message *message, bfcp_supported_list *attributes)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_SUPPORTED_PRIMITIVES</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a9edb9f990212d416bf78d01e9ff41426</anchor>
      <arglist>(bfcp_message *message, bfcp_supported_list *primitives)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_USER_DISPLAY_NAME</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>abd8c9e6fdf2ab15c31e566c0b541037e</anchor>
      <arglist>(bfcp_message *message, char *display)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_USER_URI</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a823510245a855c6e6bdcf65fddc49a59</anchor>
      <arglist>(bfcp_message *message, char *uri)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_BENEFICIARY_INFORMATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab3aa71b246b4e930c3498c249b95a33b</anchor>
      <arglist>(bfcp_message *message, bfcp_user_information *beneficiary)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_FLOOR_REQUEST_INFORMATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ade39afd811349b036fbe2b2e392f5c9e</anchor>
      <arglist>(bfcp_message *message, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_REQUESTED_BY_INFORMATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aac9e3f065deb976ff83a44eb4a919633</anchor>
      <arglist>(bfcp_message *message, bfcp_user_information *requested_by)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_FLOOR_REQUEST_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a98e5b54229853835a45a1229dd8c6f30</anchor>
      <arglist>(bfcp_message *message, bfcp_floor_request_status *fRS)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_OVERALL_REQUEST_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a4d1abdc81273891a8188c10c483c7142</anchor>
      <arglist>(bfcp_message *message, bfcp_overall_request_status *oRS)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_NONCE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a35739c4de0e6cbc2a2b5541ded725da6</anchor>
      <arglist>(bfcp_message *message, UINT16 nonce)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_DIGEST</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae7c36fd7b9a4add4e6416434c7eff56a</anchor>
      <arglist>(bfcp_message *message, bfcp_digest *digest)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>bfcp_get_length</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aad13a62152a8f07fdb2e2c0db8a5586f</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>e_bfcp_primitives</type>
      <name>bfcp_get_primitive</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a8d06eb357b6b17a7e3ee726703456e8a</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>bfcp_get_conferenceID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>afd2ec9c4a1b9ed79291657ad24d63ce5</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>bfcp_get_transactionID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a8199f4d73e9a9553227c6ed74e0c79de</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>bfcp_get_userID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ac0372326fd465e47d2a30e52094f6fbd</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_message *</type>
      <name>bfcp_new_received_message</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>adaf2672e3319c8384a07b5885fcf7c02</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_received_message</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aa6471d1e08b515febc0cd5d00480d911</anchor>
      <arglist>(bfcp_received_message *recvM)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_message_error *</type>
      <name>bfcp_received_message_add_error</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a137b7ea7f494f125106354a1f9063867</anchor>
      <arglist>(bfcp_received_message_error *error, e_bfcp_primitives attribute, e_bfcp_error_codes code)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_received_message_errors</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae310f37772da6f72c455598aec74765a</anchor>
      <arglist>(bfcp_received_message_error *errors)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_attribute *</type>
      <name>bfcp_new_received_attribute</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae3cadcf8b222ba21d8df2d483930a2fe</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_received_attribute</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a9dad9757d03960f2b653b2ff514a0a21</anchor>
      <arglist>(bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_message *</type>
      <name>bfcp_parse_message</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a87548fba3c93b5302b4d339e66547fc6</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_attribute *</type>
      <name>bfcp_parse_attribute</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a1d5b7890f74e092ede1166e2732e86d3</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_arguments</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab60f13cdc4c4de17cfaeea5870db2ccd</anchor>
      <arglist>(bfcp_received_message *recvM, bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_attribute_BENEFICIARY_ID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a68f5fc8559c66b2441cb017808b666d0</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_attribute_FLOOR_ID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a6a20de957e76b5438250991e2ed79c7b</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_attribute_FLOOR_REQUEST_ID</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a1146b2497f89e1e838adb8d2f43859c8</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>e_bfcp_priority</type>
      <name>bfcp_parse_attribute_PRIORITY</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a59aa4b19d037f3c5813d20589b8ed1cf</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_request_status *</type>
      <name>bfcp_parse_attribute_REQUEST_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ac4c0e3adbc30cad7f786a104a288f234</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_error *</type>
      <name>bfcp_parse_attribute_ERROR_CODE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a1a58a8bec53907211fab309a7876ccd9</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_ERROR_INFO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a02af1a480a90873502b77a72c0eb4663</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_PARTICIPANT_PROVIDED_INFO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a9cfb2c64251aa795e0ef0297df941f91</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_STATUS_INFO</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aeae5d4bca1d8b9e37b24885514662a71</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_supported_list *</type>
      <name>bfcp_parse_attribute_SUPPORTED_ATTRIBUTES</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a3f749db3901b111758ff81020d65c73f</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_supported_list *</type>
      <name>bfcp_parse_attribute_SUPPORTED_PRIMITIVES</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a180e7e610e0c9fea232bd36389b5fea7</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_USER_DISPLAY_NAME</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0be971d67608ca5fd0bec88b436264a5</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_USER_URI</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a8e0205fb8bff970d5275570b1896ff0a</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_user_information *</type>
      <name>bfcp_parse_attribute_BENEFICIARY_INFORMATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ab63065a2e21c2f129e4b4eb5e2384edb</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_request_information *</type>
      <name>bfcp_parse_attribute_FLOOR_REQUEST_INFORMATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae264a5b615198a2103c53532f80b4df7</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_user_information *</type>
      <name>bfcp_parse_attribute_REQUESTED_BY_INFORMATION</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>ae186a211f150d4a5f1e911d5e805094b</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_request_status *</type>
      <name>bfcp_parse_attribute_FLOOR_REQUEST_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a41d44521f4fe54549bd819bf5edbdedd</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_overall_request_status *</type>
      <name>bfcp_parse_attribute_OVERALL_REQUEST_STATUS</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a48a2a2f5252b0c0528510f521351c40a</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_attribute_NONCE</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>a0a83d1f5198b35cf23b359a61c906cfc</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_digest *</type>
      <name>bfcp_parse_attribute_DIGEST</name>
      <anchorfile>d8/d2b/bfcp__messages_8h.html</anchorfile>
      <anchor>aeb6b28114f2919badb409474e8835149</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_messages_build.c</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpmsg/</path>
    <filename>dc/d3a/bfcp__messages__build_8c</filename>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <includes id="da/dc7/bfcp__strings_8h" name="bfcp_strings.h" local="yes" imported="no">bfcp_strings.h</includes>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>ae053c5cf8237485239f8decf6420130c</anchor>
      <arglist>(bfcp_arguments *arguments)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>bfcp_build_commonheader</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a89ee55267abfe3e80e63d8af63eac301</anchor>
      <arglist>(bfcp_message *message, bfcp_entity *entity, e_bfcp_primitives primitive)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>bfcp_build_attribute_tlv</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a1463c075c4fceb97d0111f4541ee16c0</anchor>
      <arglist>(bfcp_message *message, UINT16 position, UINT16 type, UINT16 mandatory_bit, UINT16 length)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorRequest</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a1f199ef839c341efce1920f7f56452cc</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_id_list *fID, UINT16 bID, char *pInfo, e_bfcp_priority priority)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorRelease</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>adec6c394f957aaad50842c34190eb8f4</anchor>
      <arglist>(bfcp_entity *entity, UINT16 frqID)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorRequestQuery</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a0ecb176f32978b2936e01853806bc32e</anchor>
      <arglist>(bfcp_entity *entity, UINT16 frqID)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorRequestStatus</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a4493665b5fd1fc32f24b5bf698cce1f9</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_UserQuery</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>ad3cb1908446b3366aa0beec4dee8d94e</anchor>
      <arglist>(bfcp_entity *entity, UINT16 bID)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_UserStatus</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>ab69a380c46b8ff7eb39f12e26891edd1</anchor>
      <arglist>(bfcp_entity *entity, bfcp_user_information *beneficiary, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorQuery</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>adac814913ed8a8c0117cdebdf38c0f69</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_id_list *fID)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_FloorStatus</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>ae9acad985d3d8f348a4747b69875e172</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_id_list *fID, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_ChairAction</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>ae670a7d44d8ca6bca21fd19a1cc739f2</anchor>
      <arglist>(bfcp_entity *entity, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_ChairActionAck</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a8e94272e1fa23b90a5a22ecfe4bf3bf8</anchor>
      <arglist>(bfcp_entity *entity)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_Hello</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a74ad9a9ad8bc4387fcb1ee10f2bba694</anchor>
      <arglist>(bfcp_entity *entity)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_HelloAck</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a4dc220a40f33e2123d317b49410d3302</anchor>
      <arglist>(bfcp_entity *entity, bfcp_supported_list *primitives, bfcp_supported_list *attributes)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_message *</type>
      <name>bfcp_build_message_Error</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>aa19d19fcc7cade3e1135d47f436ba978</anchor>
      <arglist>(bfcp_entity *entity, bfcp_error *error, char *eInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_BENEFICIARY_ID</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a36cf3f37035eb23b1c6c34fd395b44ec</anchor>
      <arglist>(bfcp_message *message, UINT16 bID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_FLOOR_ID</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a13727ccc865967350a596bcf9e79fdf6</anchor>
      <arglist>(bfcp_message *message, UINT16 fID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_FLOOR_REQUEST_ID</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a39aa271f51960734f1f4752253d3b21d</anchor>
      <arglist>(bfcp_message *message, UINT16 frqID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_PRIORITY</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a651a9b891605a29c2afac2649aca5cdc</anchor>
      <arglist>(bfcp_message *message, e_bfcp_priority priority)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_REQUEST_STATUS</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a0d6cf216b01f4ddda23083dfd00b50b6</anchor>
      <arglist>(bfcp_message *message, bfcp_request_status *rs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_ERROR_CODE</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a4a421b3d2dbe6872efe812591de7d2fc</anchor>
      <arglist>(bfcp_message *message, bfcp_error *error)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_ERROR_INFO</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a8a3ebb6ba56055cc005cdd827615329c</anchor>
      <arglist>(bfcp_message *message, char *eInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_PARTICIPANT_PROVIDED_INFO</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a1bd53d9f1f0c5c4d05882af0d87e2a0c</anchor>
      <arglist>(bfcp_message *message, char *pInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_STATUS_INFO</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>adec2a8fe6e2cc9a0857bd13d429d8ecb</anchor>
      <arglist>(bfcp_message *message, char *sInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_SUPPORTED_ATTRIBUTES</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a8f4930b053213d4b6f8636bfcef59d44</anchor>
      <arglist>(bfcp_message *message, bfcp_supported_list *attributes)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_SUPPORTED_PRIMITIVES</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a9edb9f990212d416bf78d01e9ff41426</anchor>
      <arglist>(bfcp_message *message, bfcp_supported_list *primitives)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_USER_DISPLAY_NAME</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>abd8c9e6fdf2ab15c31e566c0b541037e</anchor>
      <arglist>(bfcp_message *message, char *display)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_USER_URI</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a823510245a855c6e6bdcf65fddc49a59</anchor>
      <arglist>(bfcp_message *message, char *uri)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_BENEFICIARY_INFORMATION</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>ab3aa71b246b4e930c3498c249b95a33b</anchor>
      <arglist>(bfcp_message *message, bfcp_user_information *beneficiary)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_FLOOR_REQUEST_INFORMATION</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>ade39afd811349b036fbe2b2e392f5c9e</anchor>
      <arglist>(bfcp_message *message, bfcp_floor_request_information *frqInfo)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_REQUESTED_BY_INFORMATION</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>aac9e3f065deb976ff83a44eb4a919633</anchor>
      <arglist>(bfcp_message *message, bfcp_user_information *requested_by)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_FLOOR_REQUEST_STATUS</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a98e5b54229853835a45a1229dd8c6f30</anchor>
      <arglist>(bfcp_message *message, bfcp_floor_request_status *fRS)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_OVERALL_REQUEST_STATUS</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a4d1abdc81273891a8188c10c483c7142</anchor>
      <arglist>(bfcp_message *message, bfcp_overall_request_status *oRS)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_NONCE</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>a35739c4de0e6cbc2a2b5541ded725da6</anchor>
      <arglist>(bfcp_message *message, UINT16 nonce)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_build_attribute_DIGEST</name>
      <anchorfile>dc/d3a/bfcp__messages__build_8c.html</anchorfile>
      <anchor>ae7c36fd7b9a4add4e6416434c7eff56a</anchor>
      <arglist>(bfcp_message *message, bfcp_digest *digest)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_messages_parse.c</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpmsg/</path>
    <filename>d8/d93/bfcp__messages__parse_8c</filename>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <includes id="da/dc7/bfcp__strings_8h" name="bfcp_strings.h" local="yes" imported="no">bfcp_strings.h</includes>
    <member kind="function">
      <type>UINT16</type>
      <name>bfcp_get_length</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>aad13a62152a8f07fdb2e2c0db8a5586f</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>e_bfcp_primitives</type>
      <name>bfcp_get_primitive</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a8d06eb357b6b17a7e3ee726703456e8a</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>UINT32</type>
      <name>bfcp_get_conferenceID</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>aabea46619ecf89ad3a7b5ff14f8126ff</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>bfcp_get_transactionID</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a8199f4d73e9a9553227c6ed74e0c79de</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>bfcp_get_userID</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>ac0372326fd465e47d2a30e52094f6fbd</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_message *</type>
      <name>bfcp_new_received_message</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>adaf2672e3319c8384a07b5885fcf7c02</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_received_message</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>aa6471d1e08b515febc0cd5d00480d911</anchor>
      <arglist>(bfcp_received_message *recvM)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_message_error *</type>
      <name>bfcp_received_message_add_error</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a137b7ea7f494f125106354a1f9063867</anchor>
      <arglist>(bfcp_received_message_error *error, e_bfcp_primitives attribute, e_bfcp_error_codes code)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_received_message_errors</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>ae310f37772da6f72c455598aec74765a</anchor>
      <arglist>(bfcp_received_message_error *errors)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_attribute *</type>
      <name>bfcp_new_received_attribute</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>ae3cadcf8b222ba21d8df2d483930a2fe</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_free_received_attribute</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a9dad9757d03960f2b653b2ff514a0a21</anchor>
      <arglist>(bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_message *</type>
      <name>bfcp_parse_message</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a87548fba3c93b5302b4d339e66547fc6</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_received_attribute *</type>
      <name>bfcp_parse_attribute</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a1d5b7890f74e092ede1166e2732e86d3</anchor>
      <arglist>(bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_arguments</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>ab60f13cdc4c4de17cfaeea5870db2ccd</anchor>
      <arglist>(bfcp_received_message *recvM, bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_attribute_BENEFICIARY_ID</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a68f5fc8559c66b2441cb017808b666d0</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_attribute_FLOOR_ID</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a6a20de957e76b5438250991e2ed79c7b</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_attribute_FLOOR_REQUEST_ID</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a1146b2497f89e1e838adb8d2f43859c8</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>e_bfcp_priority</type>
      <name>bfcp_parse_attribute_PRIORITY</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a59aa4b19d037f3c5813d20589b8ed1cf</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_request_status *</type>
      <name>bfcp_parse_attribute_REQUEST_STATUS</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>ac4c0e3adbc30cad7f786a104a288f234</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_error *</type>
      <name>bfcp_parse_attribute_ERROR_CODE</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a1a58a8bec53907211fab309a7876ccd9</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_ERROR_INFO</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a02af1a480a90873502b77a72c0eb4663</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_PARTICIPANT_PROVIDED_INFO</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a9cfb2c64251aa795e0ef0297df941f91</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_STATUS_INFO</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>aeae5d4bca1d8b9e37b24885514662a71</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_supported_list *</type>
      <name>bfcp_parse_attribute_SUPPORTED_ATTRIBUTES</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a3f749db3901b111758ff81020d65c73f</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_supported_list *</type>
      <name>bfcp_parse_attribute_SUPPORTED_PRIMITIVES</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a180e7e610e0c9fea232bd36389b5fea7</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_USER_DISPLAY_NAME</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a0be971d67608ca5fd0bec88b436264a5</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>bfcp_parse_attribute_USER_URI</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a8e0205fb8bff970d5275570b1896ff0a</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_user_information *</type>
      <name>bfcp_parse_attribute_BENEFICIARY_INFORMATION</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>ab63065a2e21c2f129e4b4eb5e2384edb</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_request_information *</type>
      <name>bfcp_parse_attribute_FLOOR_REQUEST_INFORMATION</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>ae264a5b615198a2103c53532f80b4df7</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_user_information *</type>
      <name>bfcp_parse_attribute_REQUESTED_BY_INFORMATION</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>ae186a211f150d4a5f1e911d5e805094b</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_floor_request_status *</type>
      <name>bfcp_parse_attribute_FLOOR_REQUEST_STATUS</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a41d44521f4fe54549bd819bf5edbdedd</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_overall_request_status *</type>
      <name>bfcp_parse_attribute_OVERALL_REQUEST_STATUS</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a48a2a2f5252b0c0528510f521351c40a</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_parse_attribute_NONCE</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>a0a83d1f5198b35cf23b359a61c906cfc</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
    <member kind="function">
      <type>bfcp_digest *</type>
      <name>bfcp_parse_attribute_DIGEST</name>
      <anchorfile>d8/d93/bfcp__messages__parse_8c.html</anchorfile>
      <anchor>aeb6b28114f2919badb409474e8835149</anchor>
      <arglist>(bfcp_message *message, bfcp_received_attribute *recvA)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_participant.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpcli/</path>
    <filename>da/d53/bfcp__participant_8cpp</filename>
    <includes id="d4/dd6/BFCPexception_8h" name="BFCPexception.h" local="yes" imported="no">BFCPexception.h</includes>
    <includes id="d8/dc1/bfcp__participant_8h" name="bfcp_participant.h" local="yes" imported="no">bfcp_participant.h</includes>
    <includes id="da/dc7/bfcp__strings_8h" name="bfcp_strings.h" local="yes" imported="no">bfcp_strings.h</includes>
    <includes id="db/d06/stdafx_8h" name="stdafx.h" local="yes" imported="no">stdafx.h</includes>
    <includes id="de/def/bfcp__threads_8h" name="bfcp_threads.h" local="yes" imported="no">bfcp_threads.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_SEND_CHECK_ERRORS</name>
      <anchorfile>da/d53/bfcp__participant_8cpp.html</anchorfile>
      <anchor>a08931b5173eb66ec968f5c0a6579bb33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_ParticpantLog</name>
      <anchorfile>da/d53/bfcp__participant_8cpp.html</anchorfile>
      <anchor>a078bb03ee9abd0f6d1b8dd17ed22455e</anchor>
      <arglist>(char *pcFile, int iLine, int iErrorLevel, char *pcFormat,...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_participant.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpcli/</path>
    <filename>d8/dc1/bfcp__participant_8h</filename>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <includes id="d7/dd7/BFCPconnection_8h" name="BFCPconnection.h" local="yes" imported="no">BFCPconnection.h</includes>
    <includes id="d7/d66/BFCP__fsm_8h" name="BFCP_fsm.h" local="yes" imported="no">BFCP_fsm.h</includes>
    <includes id="de/def/bfcp__threads_8h" name="bfcp_threads.h" local="yes" imported="no">bfcp_threads.h</includes>
    <class kind="struct">bfcp_floors_participant</class>
    <class kind="struct">st_bfcp_participant_information</class>
    <class kind="class">BFCP_Participant</class>
    <class kind="class">BFCP_Participant::ParticipantEvent</class>
    <member kind="typedef">
      <type>struct bfcp_floors_participant</type>
      <name>st_bfcp_floors_participant</name>
      <anchorfile>d8/dc1/bfcp__participant_8h.html</anchorfile>
      <anchor>a016549ec4539e1f178716909a0158238</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>BFCP_porting.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d5/da7/BFCP__porting_8h</filename>
  </compound>
  <compound kind="file">
    <name>BFCP_SDPStrings.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d1/d8d/BFCP__SDPStrings_8h</filename>
  </compound>
  <compound kind="file">
    <name>bfcp_server.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpsrv/</path>
    <filename>db/d2b/bfcp__server_8cpp</filename>
    <includes id="db/d06/stdafx_8h" name="stdafx.h" local="yes" imported="no">stdafx.h</includes>
    <includes id="d4/dd6/BFCPexception_8h" name="BFCPexception.h" local="yes" imported="no">BFCPexception.h</includes>
    <includes id="d7/d10/bfcp__server_8h" name="bfcp_server.h" local="yes" imported="no">bfcp_server.h</includes>
    <includes id="d6/d95/bfcp__link__list_8h" name="bfcp_link_list.h" local="yes" imported="no">bfcp_link_list.h</includes>
    <includes id="da/dc7/bfcp__strings_8h" name="bfcp_strings.h" local="yes" imported="no">bfcp_strings.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_SEND_CHECK_ERRORS</name>
      <anchorfile>db/d2b/bfcp__server_8cpp.html</anchorfile>
      <anchor>a08931b5173eb66ec968f5c0a6579bb33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_ServerLog</name>
      <anchorfile>db/d2b/bfcp__server_8cpp.html</anchorfile>
      <anchor>ac596dd72a70f2b5d855746fd0115a360</anchor>
      <arglist>(char *pcFile, int iLine, int iErrorLevel, char *pcFormat,...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_server.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpsrv/</path>
    <filename>d7/d10/bfcp__server_8h</filename>
    <includes id="d7/dd7/BFCPconnection_8h" name="BFCPconnection.h" local="yes" imported="no">BFCPconnection.h</includes>
    <includes id="d7/d66/BFCP__fsm_8h" name="BFCP_fsm.h" local="yes" imported="no">BFCP_fsm.h</includes>
    <includes id="de/def/bfcp__threads_8h" name="bfcp_threads.h" local="yes" imported="no">bfcp_threads.h</includes>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <includes id="d3/d20/bfcp__user__list_8h" name="bfcp_user_list.h" local="yes" imported="no">bfcp_user_list.h</includes>
    <includes id="d6/d95/bfcp__link__list_8h" name="bfcp_link_list.h" local="yes" imported="no">bfcp_link_list.h</includes>
    <class kind="struct">st_bfcp_conference</class>
    <class kind="struct">st_bfcp_server</class>
    <class kind="class">BFCP_Server</class>
    <class kind="class">BFCP_Server::ServerEvent</class>
    <class kind="struct">bfcp_thread</class>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_SERVER_BASE_CONFID</name>
      <anchorfile>d7/d10/bfcp__server_8h.html</anchorfile>
      <anchor>adec37f264210a8ff22e63245631a8867</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_SERVER_BASE_USERID</name>
      <anchorfile>d7/d10/bfcp__server_8h.html</anchorfile>
      <anchor>a0beb82e4c6877a3a6cc3738c8d13de71</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_SERVER_BASE_FLOORID</name>
      <anchorfile>d7/d10/bfcp__server_8h.html</anchorfile>
      <anchor>ab29917e36a4fc9abdd9fdbcc0f0921c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_SERVER_BASE_STREAMID</name>
      <anchorfile>d7/d10/bfcp__server_8h.html</anchorfile>
      <anchor>a3cd24a964ecf9025da475385d62ebcf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_thread</type>
      <name>bfcp_thread</name>
      <anchorfile>d7/d10/bfcp__server_8h.html</anchorfile>
      <anchor>a9d13692ac8dfb9c9cfe0e9f3cda3b3f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bfcp_thread *</type>
      <name>struct_thread</name>
      <anchorfile>d7/d10/bfcp__server_8h.html</anchorfile>
      <anchor>a8eec0794cf303f2eb3e65025cc7dd0d8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_strings.c</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpmsg/</path>
    <filename>d0/d07/bfcp__strings_8c</filename>
    <includes id="da/dc7/bfcp__strings_8h" name="bfcp_strings.h" local="yes" imported="no">bfcp_strings.h</includes>
    <class kind="struct">_bfcp_primitives</class>
    <class kind="struct">_bfcp_attributes</class>
    <class kind="struct">_bfcp_statuses</class>
    <class kind="struct">_bfcp_priorities</class>
    <class kind="struct">_bfcp_error_types</class>
    <class kind="struct">_bfcp_parsing_errors</class>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpDescPrimitive</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>ad8056ca727b9b62512e70e905640ecfb</anchor>
      <arglist>(e_bfcp_primitives p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpAttribute</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>a4535d7019ec48601cc7987fdd803c7dd</anchor>
      <arglist>(e_bfcp_attibutes p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpStatus</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>afcced51ec79770f0f2a4157c319615a1</anchor>
      <arglist>(e_bfcp_status p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpPriority</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>a8a9f9705a1a5d00723fec9594e0bdd07</anchor>
      <arglist>(e_bfcp_priority p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpErrorType</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>a14acf1afd3b55378fa876f07d8632b56</anchor>
      <arglist>(e_bfcp_error_codes p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpParsingErrors</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>a7cc94201300408ec979167bf57f36e4f</anchor>
      <arglist>(e_bfcp_specific_error_codes p)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static struct _bfcp_primitives</type>
      <name>_bfcp_primitive</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>a85cbaed3c3dcbebc821eb055e9a2e2a7</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static struct _bfcp_attributes</type>
      <name>_bfcp_attribute</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>a71eaf680ec7fc48a736530c149443e44</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static struct _bfcp_statuses</type>
      <name>_bfcp_status</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>afd03dc5966477653107e559bb7835ca3</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static struct _bfcp_priorities</type>
      <name>_bfcp_priority</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>a51e293b3bb3c9bef34f530a5d150cabe</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static struct _bfcp_error_types</type>
      <name>_bfcp_error_type</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>a778a2f6bb55ae8e32fa00cd6f2962ebf</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static struct _bfcp_parsing_errors</type>
      <name>_bfcp_parsing_error</name>
      <anchorfile>d0/d07/bfcp__strings_8c.html</anchorfile>
      <anchor>a13db53b9cd6603fc709e9272777d075b</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_strings.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpmsg/</path>
    <filename>da/dc7/bfcp__strings_8h</filename>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpDescPrimitive</name>
      <anchorfile>da/dc7/bfcp__strings_8h.html</anchorfile>
      <anchor>ad8056ca727b9b62512e70e905640ecfb</anchor>
      <arglist>(e_bfcp_primitives p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpAttribute</name>
      <anchorfile>da/dc7/bfcp__strings_8h.html</anchorfile>
      <anchor>a4535d7019ec48601cc7987fdd803c7dd</anchor>
      <arglist>(e_bfcp_attibutes p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpStatus</name>
      <anchorfile>da/dc7/bfcp__strings_8h.html</anchorfile>
      <anchor>afcced51ec79770f0f2a4157c319615a1</anchor>
      <arglist>(e_bfcp_status p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpPriority</name>
      <anchorfile>da/dc7/bfcp__strings_8h.html</anchorfile>
      <anchor>a8a9f9705a1a5d00723fec9594e0bdd07</anchor>
      <arglist>(e_bfcp_priority p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpErrorType</name>
      <anchorfile>da/dc7/bfcp__strings_8h.html</anchorfile>
      <anchor>a14acf1afd3b55378fa876f07d8632b56</anchor>
      <arglist>(e_bfcp_error_codes p)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpParsingErrors</name>
      <anchorfile>da/dc7/bfcp__strings_8h.html</anchorfile>
      <anchor>a7cc94201300408ec979167bf57f36e4f</anchor>
      <arglist>(e_bfcp_specific_error_codes p)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_threads.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>de/def/bfcp__threads_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>bfcp_mutex_init</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>afdfd21a0226d1e0a8e398f0dddc360e6</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>bfcp_mutex_destroy</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>ae4be8fed8a6a11b511d7908f998a3cd0</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>bfcp_mutex_lock</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>a720a9b5511e5edbaa3063e52039c2d31</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>bfcp_mutex_unlock</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>a5a3ae00cfbfff7da56f720ca53879c11</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_THREAD_HANDLE</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>a6b54b88e0f97fda3f4eae439990d5617</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_THREAD_START</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>a0317bfeb7c6f4d64fa07d44fde4eadaa</anchor>
      <arglist>(threadID, ThreadFunc, arg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_THREAD_KILL</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>ab70c087f8c7327c6fe72d4fc39aa48ec</anchor>
      <arglist>(HThread)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_NULL_THREAD_HANDLE</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>aa7c931a4eef184c9511f44f0a3cc5532</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_SLEEP</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>a81adfd5a8e961787e1abc109484f9d12</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="typedef">
      <type>pthread_mutex_t</type>
      <name>bfcp_mutex_t</name>
      <anchorfile>de/def/bfcp__threads_8h.html</anchorfile>
      <anchor>aec431870c7be0617f5ad632bae9520fa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bfcp_user_list.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpsrv/</path>
    <filename>d1/d17/bfcp__user__list_8cpp</filename>
    <includes id="de/def/bfcp__threads_8h" name="bfcp_threads.h" local="yes" imported="no">../../bfcp_threads.h</includes>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <includes id="d3/d20/bfcp__user__list_8h" name="bfcp_user_list.h" local="yes" imported="no">bfcp_user_list.h</includes>
    <includes id="d4/dd6/BFCPexception_8h" name="BFCPexception.h" local="yes" imported="no">BFCPexception.h</includes>
  </compound>
  <compound kind="file">
    <name>bfcp_user_list.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpsrv/</path>
    <filename>d3/d20/bfcp__user__list_8h</filename>
    <class kind="struct">bfcp_user</class>
    <class kind="struct">bfcp_list_users</class>
    <class kind="class">BFCP_UserList</class>
    <member kind="typedef">
      <type>struct bfcp_user</type>
      <name>bfcp_user</name>
      <anchorfile>d3/d20/bfcp__user__list_8h.html</anchorfile>
      <anchor>a038641710e3894b60e9be52937ef587b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bfcp_user *</type>
      <name>users</name>
      <anchorfile>d3/d20/bfcp__user__list_8h.html</anchorfile>
      <anchor>a76faed6b1d798d7c829a1c7dd1ffeeec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bfcp_list_users</type>
      <name>bfcp_list_users</name>
      <anchorfile>d3/d20/bfcp__user__list_8h.html</anchorfile>
      <anchor>a823e36b3fcf9a72a1f4ab8a1bb0809d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bfcp_list_users *</type>
      <name>lusers</name>
      <anchorfile>d3/d20/bfcp__user__list_8h.html</anchorfile>
      <anchor>a498aa49bac24e7f349fd37055e8e9d94</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>chair_type</name>
      <anchorfile>d3/d20/bfcp__user__list_8h.html</anchorfile>
      <anchor>a925b14d6a1f072d65af4254ad732003c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NO_CHAIR</name>
      <anchorfile>d3/d20/bfcp__user__list_8h.html</anchorfile>
      <anchor>a925b14d6a1f072d65af4254ad732003cadd809303e44f4531d47088402b54dccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CHAIR</name>
      <anchorfile>d3/d20/bfcp__user__list_8h.html</anchorfile>
      <anchor>a925b14d6a1f072d65af4254ad732003ca5e17eb38adb4fb5e119e94614b878809</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>BFCPapi.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>da/dd4/BFCPapi_8cpp</filename>
    <includes id="db/d06/stdafx_8h" name="stdafx.h" local="yes" imported="no">stdafx.h</includes>
    <includes id="d2/d8a/BFCPapi_8h" name="BFCPapi.h" local="yes" imported="no">BFCPapi.h</includes>
    <includes id="d1/d8d/BFCP__SDPStrings_8h" name="BFCP_SDPStrings.h" local="yes" imported="no">BFCP_SDPStrings.h</includes>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <includes id="da/dc7/bfcp__strings_8h" name="bfcp_strings.h" local="yes" imported="no">bfcp_strings.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>SERVER_DEFAULT_USERID</name>
      <anchorfile>da/dd4/BFCPapi_8cpp.html</anchorfile>
      <anchor>a0b8e0322144af112985cb290be0e43e4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>BFCPapi.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d2/d8a/BFCPapi_8h</filename>
    <includes id="d8/dc1/bfcp__participant_8h" name="bfcp_participant.h" local="yes" imported="no">BFCP_participant.h</includes>
    <includes id="d7/d10/bfcp__server_8h" name="bfcp_server.h" local="yes" imported="no">BFCP_Server.h</includes>
    <class kind="class">BFCPApi</class>
    <class kind="class">BFCPApi::BFCPApiEvent</class>
    <class kind="struct">_bfcp_floorctrlModes</class>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_API</name>
      <anchorfile>d2/d8a/BFCPapi_8h.html</anchorfile>
      <anchor>a8b254a63791f96e16c8ba4abeec7cce6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCPAPI_SUCCESS</name>
      <anchorfile>d2/d8a/BFCPapi_8h.html</anchorfile>
      <anchor>a10e9d1709a8a98278712406597f9cc1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCPAPI_ERROR</name>
      <anchorfile>d2/d8a/BFCPapi_8h.html</anchorfile>
      <anchor>a0e3559ecec451a59dc205a026c4216be</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getBfcpFloorctrlMode</name>
      <anchorfile>d2/d8a/BFCPapi_8h.html</anchorfile>
      <anchor>a5f0ea95a717144233e7b1a37b3874506</anchor>
      <arglist>(UINT32 p)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static struct _bfcp_floorctrlModes</type>
      <name>_bfcp_floorctrlMode</name>
      <anchorfile>d2/d8a/BFCPapi_8h.html</anchorfile>
      <anchor>a24c56ba01ab8a62c19d5de1ffb305fc9</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>BFCPconnection.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d4/d7d/BFCPconnection_8cpp</filename>
    <includes id="db/d06/stdafx_8h" name="stdafx.h" local="yes" imported="no">stdafx.h</includes>
    <includes id="d7/dd7/BFCPconnection_8h" name="BFCPconnection.h" local="yes" imported="no">BFCPconnection.h</includes>
    <includes id="d4/dd6/BFCPexception_8h" name="BFCPexception.h" local="yes" imported="no">BFCPexception.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>_GETLASTERROR</name>
      <anchorfile>d4/d7d/BFCPconnection_8cpp.html</anchorfile>
      <anchor>aceb18920d91d6edc31bda04c24d15b7c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>BFCPconnection.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d7/dd7/BFCPconnection_8h</filename>
    <includes id="d8/d2b/bfcp__messages_8h" name="bfcp_messages.h" local="yes" imported="no">bfcp_messages.h</includes>
    <includes id="de/def/bfcp__threads_8h" name="bfcp_threads.h" local="yes" imported="no">bfcp_threads.h</includes>
    <class kind="class">BFCPConnection</class>
    <class kind="struct">BFCPConnection::Client2ServerInfo</class>
    <class kind="class">BFCPConnectionRole</class>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_OVER_TCP</name>
      <anchorfile>d7/dd7/BFCPconnection_8h.html</anchorfile>
      <anchor>a6732640e5be7c4ea0a533240a244fcb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_OVER_TLS</name>
      <anchorfile>d7/dd7/BFCPconnection_8h.html</anchorfile>
      <anchor>a12d210c7c6ba5f5af559dc5dfdf7f090</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_FCS_DEFAULT_PORT</name>
      <anchorfile>d7/dd7/BFCPconnection_8h.html</anchorfile>
      <anchor>a113032f68178e7eee6017229227d49d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_MAX_CONF</name>
      <anchorfile>d7/dd7/BFCPconnection_8h.html</anchorfile>
      <anchor>aa2f0ed429cb40bcc0ac4ec66bf756295</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_BACKLOG</name>
      <anchorfile>d7/dd7/BFCPconnection_8h.html</anchorfile>
      <anchor>a1d1af8315090f2ad5d0bd41edd3328a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_MAX_CONNECTIONS</name>
      <anchorfile>d7/dd7/BFCPconnection_8h.html</anchorfile>
      <anchor>a7439fde0650524c281969b5760889162</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>BFCPexception.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d4/dd6/BFCPexception_8h</filename>
    <class kind="class">BFCPException</class>
    <class kind="class">InterruptedException</class>
    <class kind="class">UnknownHostException</class>
    <class kind="class">FileNotFoundException</class>
    <class kind="class">InvalidParameterException</class>
    <class kind="class">OpenFileErrorException</class>
    <class kind="class">IOException</class>
    <class kind="class">IllegalArgumentException</class>
    <class kind="class">ParseException</class>
    <class kind="class">BadParameterException</class>
    <class kind="class">SessionCondemnedException</class>
    <class kind="class">RequestMethodException</class>
    <class kind="class">PayloadOverflowException</class>
    <class kind="class">MessageMissformedException</class>
    <class kind="class">BadMessageSchemeException</class>
    <class kind="class">InternalProgramError</class>
    <class kind="class">InvalidFieldException</class>
  </compound>
  <compound kind="file">
    <name>BFCPinputstream.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d6/dba/BFCPinputstream_8cpp</filename>
    <includes id="db/d06/stdafx_8h" name="stdafx.h" local="yes" imported="no">stdafx.h</includes>
    <includes id="da/de2/BFCPinputstream_8h" name="BFCPinputstream.h" local="yes" imported="no">BFCPinputstream.h</includes>
    <includes id="d4/dd6/BFCPexception_8h" name="BFCPexception.h" local="yes" imported="no">BFCPexception.h</includes>
  </compound>
  <compound kind="file">
    <name>BFCPinputstream.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>da/de2/BFCPinputstream_8h</filename>
    <class kind="class">BFCPinputstream</class>
    <class kind="class">FileBFCPinputstream</class>
    <class kind="class">ByteArrayBFCPinputstream</class>
    <class kind="class">SocketBFCPinputstream</class>
  </compound>
  <compound kind="file">
    <name>BFCPoutputstream.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d3/dc6/BFCPoutputstream_8cpp</filename>
    <includes id="db/d06/stdafx_8h" name="stdafx.h" local="yes" imported="no">stdafx.h</includes>
    <includes id="da/d75/BFCPoutputstream_8h" name="BFCPoutputstream.h" local="yes" imported="no">BFCPOutputStream.h</includes>
    <includes id="d4/dd6/BFCPexception_8h" name="BFCPexception.h" local="yes" imported="no">BFCPexception.h</includes>
  </compound>
  <compound kind="file">
    <name>BFCPoutputstream.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>da/d75/BFCPoutputstream_8h</filename>
    <class kind="class">BFCPOutputStream</class>
    <class kind="class">FileBFCPOutputStream</class>
    <class kind="class">SocketBFCPOutputStream</class>
  </compound>
  <compound kind="file">
    <name>client.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/samples/</path>
    <filename>d9/d95/client_8cpp</filename>
    <includes id="d8/de1/client_8h" name="client.h" local="yes" imported="no">client.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_CHECK_INTEGER</name>
      <anchorfile>d9/d95/client_8cpp.html</anchorfile>
      <anchor>a64e0c9ae8acbba6c0d63cb3ecf1330aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>d9/d95/client_8cpp.html</anchorfile>
      <anchor>a0ddf1224851353fc92bfbff6f499fa97</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>client.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/samples/</path>
    <filename>d8/de1/client_8h</filename>
    <includes id="d8/dc1/bfcp__participant_8h" name="bfcp_participant.h" local="no" imported="no">bfcp_participant.h</includes>
    <class kind="class">sampleClient</class>
    <member kind="define">
      <type>#define</type>
      <name>BFCPAPI_SUCCESS</name>
      <anchorfile>d8/de1/client_8h.html</anchorfile>
      <anchor>a10e9d1709a8a98278712406597f9cc1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCPAPI_ERROR</name>
      <anchorfile>d8/de1/client_8h.html</anchorfile>
      <anchor>a0e3559ecec451a59dc205a026c4216be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>e_floorctrlMode</name>
      <anchorfile>d8/de1/client_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_CLIENT</name>
      <anchorfile>d8/de1/client_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874a472f13da8a62c68e6778b6e4d1b8a6f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_SERVER</name>
      <anchorfile>d8/de1/client_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874a4d7374fcfc4f3943d85ef30fd15f5e20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_CLIENT_AND_SERVER</name>
      <anchorfile>d8/de1/client_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874adc85d4891a4cfd0719834f6cb0f40ea4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_CLIENT</name>
      <anchorfile>d8/de1/client_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874a472f13da8a62c68e6778b6e4d1b8a6f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_SERVER</name>
      <anchorfile>d8/de1/client_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874a4d7374fcfc4f3943d85ef30fd15f5e20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_CLIENT_AND_SERVER</name>
      <anchorfile>d8/de1/client_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874adc85d4891a4cfd0719834f6cb0f40ea4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>libbfcp.txt</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/</path>
    <filename>de/d5e/libbfcp_8txt</filename>
  </compound>
  <compound kind="file">
    <name>resource.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d8/d01/resource_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>IDD_DIALOG_BFCP_WINDOW_SHARING</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a7b645aac2d3a992464b3f287a50367a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDB_BITMAP_LIVE</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>aeb841141546c6696edfcd721ce94645c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDB_BITMAP_PRESENTATION</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>afd9ed066cdd2829125c52b010915bfdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDB_BITMAP_LIVE_DISABLE</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a83223a597627abfa81e124972709f105</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDB_BITMAP_PRESENTATION_DISABLE</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>aad643e3cf273419c01c270bba75ca670</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDB_BITMAP_LIVE_DISABLE1</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a13af2cc66f54c33f2bbd26d326e0dd9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDB_BITMAP_PRESENTATION_DISABLE1</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>adbbd1d474ff5606b6fb13f34a82d3166</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_BUTTON_LIVE_CONTENT</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a354d2d3a3e0f0ad7e63012ceeb06e19a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_BUTTON_PRESENTATION_CONTENT</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>ab188ec8cb4bb5a9125f3fe1e4d0f4182</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_STATIC_BORDER</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a0a8dee187400565e02441e7789743003</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_STATIC_PRESENTATION</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a84ca0ce0202653fc8aee10d56d9f3eb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_STATIC_LIVE</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a8bab785cfdf05ae9be183f478a56f5d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_LIST_WINDOWS</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a38c9c5c201773269db57a4cd2030748d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_BTN_REFRESH</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a8f0bf2c8d8c7d971d049ee67c2ebafb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_BTN_VIDEOOPTIONS</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>af55073b2200d8cbd7f19bd4545afaa82</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_BTN_SENDINTRA</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>ae9ac4bfac0633680bc8becda37a3dda6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_STATIC_VIDEOQUALITY</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a38d2a4ea24019003f33b58d4cd5a567f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_STATIC_SENDINTRA</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a8bca4a88f8692529fda2831e9accaa24</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_CK_ALLOW_1024_768</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a1c17dd36ef9e63736c77653eeb421841</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_CK_ALLOW_640_480</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a0b899cd3390f7858ce05285b677548c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDC_VIDEO_QUALITY</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a78cf7d54a46229fa5ee704f72e2471a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDS_TXT_FONT_NAME</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a59198c28f561e0dcdf03d1a205f5cd9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDS_TXT_FONT_SIZE</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a69ab976b5e33dad0b284668664bdb9f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDS_TXT_PRESENTATION</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a149ca8ad5bccfd29d1c0030be88af900</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDS_TXT_LIVE</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a9d2a03ae2785d630db601151304ad707</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDS_BTN_REFRESH_LIST</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a129db104446aae1dc52628bb0062e4d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDS_PLUGIN_TITLE</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>af2a566eed1a1d76396c54996326b05c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDS_BTN_VIDEOOPTION_OFF</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>a41ed99cffcf1d06d02e19682a1ef9a6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDS_BTN_VIDEOOPTION_ON</name>
      <anchorfile>d8/d01/resource_8h.html</anchorfile>
      <anchor>ab3651e6325faa202631d61ea8cbeaa8f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>server.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/samples/</path>
    <filename>df/dd7/server_8cpp</filename>
    <includes id="d8/dc3/server_8h" name="server.h" local="yes" imported="no">server.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>BFCP_CHECK_INTEGER</name>
      <anchorfile>df/dd7/server_8cpp.html</anchorfile>
      <anchor>a64e0c9ae8acbba6c0d63cb3ecf1330aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>df/dd7/server_8cpp.html</anchorfile>
      <anchor>a0ddf1224851353fc92bfbff6f499fa97</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>server.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/samples/</path>
    <filename>d8/dc3/server_8h</filename>
    <includes id="d7/d10/bfcp__server_8h" name="bfcp_server.h" local="yes" imported="no">bfcp_server.h</includes>
    <class kind="class">sampleServer</class>
    <member kind="define">
      <type>#define</type>
      <name>INF</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>a12c2040f25d8e3a7b9e1c2024c618cb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WAR</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>a9423380a92639b296ea0a984ea7e1c6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERR</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>a735563036dced0b7d6cc98f97ea4978b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCPAPI_SUCCESS</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>a10e9d1709a8a98278712406597f9cc1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BFCPAPI_ERROR</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>a0e3559ecec451a59dc205a026c4216be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>e_floorctrlMode</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_CLIENT</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874a472f13da8a62c68e6778b6e4d1b8a6f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_SERVER</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874a4d7374fcfc4f3943d85ef30fd15f5e20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_CLIENT_AND_SERVER</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874adc85d4891a4cfd0719834f6cb0f40ea4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_CLIENT</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874a472f13da8a62c68e6778b6e4d1b8a6f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_SERVER</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874a4d7374fcfc4f3943d85ef30fd15f5e20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FLOOCTRL_MODE_CLIENT_AND_SERVER</name>
      <anchorfile>d8/dc3/server_8h.html</anchorfile>
      <anchor>af1144ed33fa3ea563f5a17b74247c874adc85d4891a4cfd0719834f6cb0f40ea4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>stdafx.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>df/d9d/stdafx_8cpp</filename>
    <includes id="db/d06/stdafx_8h" name="stdafx.h" local="yes" imported="no">stdafx.h</includes>
    <member kind="function">
      <type>void</type>
      <name>LogInit</name>
      <anchorfile>df/d9d/stdafx_8cpp.html</anchorfile>
      <anchor>a2dec9b1a1af7c6963bec70259340d650</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>LogClose</name>
      <anchorfile>df/d9d/stdafx_8cpp.html</anchorfile>
      <anchor>af7326c1f488f20792fa8ee07f173e8a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>df/d9d/stdafx_8cpp.html</anchorfile>
      <anchor>a63bfe6b5ff4bb4d88cdde61fe22169a7</anchor>
      <arglist>(const char *pcFile, int iLine, int iErrorLevel, const char *pcFormat,...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>stdafx.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>db/d06/stdafx_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>INF</name>
      <anchorfile>db/d06/stdafx_8h.html</anchorfile>
      <anchor>a12c2040f25d8e3a7b9e1c2024c618cb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WAR</name>
      <anchorfile>db/d06/stdafx_8h.html</anchorfile>
      <anchor>a9423380a92639b296ea0a984ea7e1c6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERR</name>
      <anchorfile>db/d06/stdafx_8h.html</anchorfile>
      <anchor>a735563036dced0b7d6cc98f97ea4978b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>LogInit</name>
      <anchorfile>db/d06/stdafx_8h.html</anchorfile>
      <anchor>a2dec9b1a1af7c6963bec70259340d650</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>LogClose</name>
      <anchorfile>db/d06/stdafx_8h.html</anchorfile>
      <anchor>af7326c1f488f20792fa8ee07f173e8a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>db/d06/stdafx_8h.html</anchorfile>
      <anchor>a8e4b9cffaf29c14383992835d17f5812</anchor>
      <arglist>(const char *pcFile, int iLine, int iErrLevel, const char *pcFormat,...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>WinShareCtrl.cpp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>d5/d58/WinShareCtrl_8cpp</filename>
    <includes id="dc/d6b/WinShareCtrl_8h" name="WinShareCtrl.h" local="yes" imported="no">WinShareCtrl.h</includes>
  </compound>
  <compound kind="file">
    <name>WinShareCtrl.h</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>dc/d6b/WinShareCtrl_8h</filename>
    <class kind="class">libbfcp::WinShareCtrl</class>
    <namespace>libbfcp</namespace>
    <namespace>libbfcp</namespace>
  </compound>
  <compound kind="struct">
    <name>_bfcp_actions</name>
    <filename>d0/d08/struct__bfcp__actions.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>state</name>
      <anchorfile>d0/d08/struct__bfcp__actions.html</anchorfile>
      <anchor>a30c607154b0c2c0dbed428b748946d44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchorfile>d0/d08/struct__bfcp__actions.html</anchorfile>
      <anchor>a845878c85e62dbdd26f2b9487c8d5a6f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>_bfcp_attributes</name>
    <filename>d5/db4/struct__bfcp__attributes.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>attribute</name>
      <anchorfile>d5/db4/struct__bfcp__attributes.html</anchorfile>
      <anchor>af09212560e134bbc6192661cb86d2311</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchorfile>d5/db4/struct__bfcp__attributes.html</anchorfile>
      <anchor>aa15376a063b8e95195d3ebfef2cd55c7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>_bfcp_error_types</name>
    <filename>da/d0b/struct__bfcp__error__types.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>error</name>
      <anchorfile>da/d0b/struct__bfcp__error__types.html</anchorfile>
      <anchor>a4a420ca81198a3e1a7c31a35e606d4f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchorfile>da/d0b/struct__bfcp__error__types.html</anchorfile>
      <anchor>a23756042841a79cbcabf3733d88478fe</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>_bfcp_floorctrlModes</name>
    <filename>d9/dd8/struct__bfcp__floorctrlModes.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>floorctrlMode</name>
      <anchorfile>d9/dd8/struct__bfcp__floorctrlModes.html</anchorfile>
      <anchor>a657aa8c8285d99e87f3376a1e3a4de27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchorfile>d9/dd8/struct__bfcp__floorctrlModes.html</anchorfile>
      <anchor>a47abe469c4a8ddffd17c5cdaa168ea40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>UpperDescription</name>
      <anchorfile>d9/dd8/struct__bfcp__floorctrlModes.html</anchorfile>
      <anchor>a6544911ca0bca02cb628ec1934149ddc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>_bfcp_parsing_errors</name>
    <filename>db/d1c/struct__bfcp__parsing__errors.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>error</name>
      <anchorfile>db/d1c/struct__bfcp__parsing__errors.html</anchorfile>
      <anchor>ac8527e9106d4ad832e64c3456fec1429</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchorfile>db/d1c/struct__bfcp__parsing__errors.html</anchorfile>
      <anchor>a1aa359870c2c989e4c05a5dcb2312b44</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>_bfcp_primitives</name>
    <filename>da/d1f/struct__bfcp__primitives.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>primitive</name>
      <anchorfile>da/d1f/struct__bfcp__primitives.html</anchorfile>
      <anchor>aa079a9cdb2291e5d3c2c5dc693518fff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchorfile>da/d1f/struct__bfcp__primitives.html</anchorfile>
      <anchor>afaac653c6b372d357dbfa43b8bce8fdf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>_bfcp_priorities</name>
    <filename>d0/dda/struct__bfcp__priorities.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>priority</name>
      <anchorfile>d0/dda/struct__bfcp__priorities.html</anchorfile>
      <anchor>ad0f25de8f92be8bac233332bb11870fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchorfile>d0/dda/struct__bfcp__priorities.html</anchorfile>
      <anchor>a7a8df30a3ad254a62d737f7ee4653358</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>_bfcp_statuses</name>
    <filename>d5/d31/struct__bfcp__statuses.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>status</name>
      <anchorfile>d5/d31/struct__bfcp__statuses.html</anchorfile>
      <anchor>ac15ca4b33f191ba9157fca404567e375</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchorfile>d5/d31/struct__bfcp__statuses.html</anchorfile>
      <anchor>abe0cb23886356622257741c6a2740eea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BadMessageSchemeException</name>
    <filename>d6/ddf/classBadMessageSchemeException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>BadMessageSchemeException</name>
      <anchorfile>d6/ddf/classBadMessageSchemeException.html</anchorfile>
      <anchor>adf7c82e527ca798b951e17685b877c3a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BadMessageSchemeException</name>
      <anchorfile>d6/ddf/classBadMessageSchemeException.html</anchorfile>
      <anchor>ae92600ab47dd11afbe22a75938532276</anchor>
      <arglist>(const char *message)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCPException</name>
      <anchorfile>de/dea/classBFCPException.html</anchorfile>
      <anchor>a81c2d62be790f42751c117d91d92c814</anchor>
      <arglist>(const char *file, const int line, bool fatal, const char *reason=&quot;Unknown&quot;, const char *comment=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCPException</name>
      <anchorfile>de/dea/classBFCPException.html</anchorfile>
      <anchor>a84b7ecb638be742c5e68f63dfd1656b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BFCPException</name>
      <anchorfile>de/dea/classBFCPException.html</anchorfile>
      <anchor>aa9636b38fed3c5dd097cd99356d0cef9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>what</name>
      <anchorfile>de/dea/classBFCPException.html</anchorfile>
      <anchor>a21c161a9b2ca62e08aa8c5a10e4d0d21</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BadParameterException</name>
    <filename>d4/dac/classBadParameterException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>BadParameterException</name>
      <anchorfile>d4/dac/classBadParameterException.html</anchorfile>
      <anchor>a61c8075c7e54cf3bacdb816e8a0e9396</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BadParameterException</name>
      <anchorfile>d4/dac/classBadParameterException.html</anchorfile>
      <anchor>a0967a342c484d36c4df508f8f1fd0987</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_arguments</name>
    <filename>de/d1a/structbfcp__arguments.html</filename>
    <member kind="variable">
      <type>e_bfcp_primitives</type>
      <name>primitive</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>aaeba9d262e62d41284daed1bd902b688</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_entity *</type>
      <name>entity</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a83e45612a435fea90f006a898de8ddd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_floor_id_list *</type>
      <name>fID</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>afb4922027487b4f88e93b817d1497f0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>frqID</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a28460ad47739da1e7574f9824019bf41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>bID</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a3e663ee1a929e8d24f096152d8b6f05e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_priority</type>
      <name>priority</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>ae71c77c80181a5398beaeb082eb27925</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_floor_request_information *</type>
      <name>frqInfo</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a77a5e136ff72152842c49d60ce0ed3ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_user_information *</type>
      <name>beneficiary</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a6b74ee841a9b2b4cf17af14e3a17ebad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_request_status *</type>
      <name>rs</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a9ee9957acfe175f6f43f43b2d85c724a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>pInfo</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a320adb295986f186bb752bc98e33d9bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>sInfo</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>aa256ae3f27fd35988027ff708f101d30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_error *</type>
      <name>error</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a6f4ab0b642f2971ac2963752f65a2a6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>eInfo</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a9c9862a229ec7e48de890e78ffd387fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_supported_list *</type>
      <name>primitives</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>aa7e484d44c4242b95cfbe96749985b43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_supported_list *</type>
      <name>attributes</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a2af6e4adbcf07fdbf79cf05842339477</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>nonce</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>aa4f7d8da1191c4f5a9316a7e878d7f03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_digest *</type>
      <name>digest</name>
      <anchorfile>de/d1a/structbfcp__arguments.html</anchorfile>
      <anchor>a643f18069698d5ddb45523b168e543f4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_digest</name>
    <filename>df/da4/structbfcp__digest.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>algorithm</name>
      <anchorfile>df/da4/structbfcp__digest.html</anchorfile>
      <anchor>ac0650904c9e4e34bafb451718570dcab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>text</name>
      <anchorfile>df/da4/structbfcp__digest.html</anchorfile>
      <anchor>a3e91a71e8028d0399970ee4fdf522c39</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_entity</name>
    <filename>d8/d81/structbfcp__entity.html</filename>
    <member kind="variable">
      <type>UINT32</type>
      <name>conferenceID</name>
      <anchorfile>d8/d81/structbfcp__entity.html</anchorfile>
      <anchor>ad8e7442d0b53fded3a37d0e042a693bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>transactionID</name>
      <anchorfile>d8/d81/structbfcp__entity.html</anchorfile>
      <anchor>a04e4254f6a1f86c1fcf148fe279f60e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>userID</name>
      <anchorfile>d8/d81/structbfcp__entity.html</anchorfile>
      <anchor>a8c83f946f05d81722e69a69515c33676</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_error</name>
    <filename>df/df1/structbfcp__error.html</filename>
    <member kind="variable">
      <type>e_bfcp_error_codes</type>
      <name>code</name>
      <anchorfile>df/df1/structbfcp__error.html</anchorfile>
      <anchor>a082849a978d73fcb5c2148a48fa04f96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_unknown_m_error_details *</type>
      <name>details</name>
      <anchorfile>df/df1/structbfcp__error.html</anchorfile>
      <anchor>aa4b505ac3c5524d3e365d7e85237d663</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_floor</name>
    <filename>d2/d14/structbfcp__floor.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>floorID</name>
      <anchorfile>d2/d14/structbfcp__floor.html</anchorfile>
      <anchor>a98e23adb3fe9000384bbdf90cfed7d30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_floor_state</type>
      <name>status</name>
      <anchorfile>d2/d14/structbfcp__floor.html</anchorfile>
      <anchor>adaa0142d5bc42bb513ed2e6d17f31052</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>chair_info</name>
      <anchorfile>d2/d14/structbfcp__floor.html</anchorfile>
      <anchor>a82108f3cd4d8aa2a7eed729a61595361</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BFCP_THREAD_HANDLE</type>
      <name>pID</name>
      <anchorfile>d2/d14/structbfcp__floor.html</anchorfile>
      <anchor>a2de6351c8205b8685c944e9b0239fb03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_floor *</type>
      <name>next</name>
      <anchorfile>d2/d14/structbfcp__floor.html</anchorfile>
      <anchor>a6feb2602d5aa44d3979d1f7567cac4db</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_floor_id_list</name>
    <filename>db/d8b/structbfcp__floor__id__list.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>ID</name>
      <anchorfile>db/d8b/structbfcp__floor__id__list.html</anchorfile>
      <anchor>a48a9e753c8a3be9bff3ff5baa08bfcfb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_floor_id_list *</type>
      <name>next</name>
      <anchorfile>db/d8b/structbfcp__floor__id__list.html</anchorfile>
      <anchor>ade33e5504830286d84262e813d770b74</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_floor_request_information</name>
    <filename>d5/d06/structbfcp__floor__request__information.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>frqID</name>
      <anchorfile>d5/d06/structbfcp__floor__request__information.html</anchorfile>
      <anchor>aa41fa5a5fa3e69fde52aa244c5d96bc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_overall_request_status *</type>
      <name>oRS</name>
      <anchorfile>d5/d06/structbfcp__floor__request__information.html</anchorfile>
      <anchor>a43c21b874c18a0461178f879aee6d3a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_floor_request_status *</type>
      <name>fRS</name>
      <anchorfile>d5/d06/structbfcp__floor__request__information.html</anchorfile>
      <anchor>a613368af58e7c4fbbaecdc32d6c01826</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_user_information *</type>
      <name>beneficiary</name>
      <anchorfile>d5/d06/structbfcp__floor__request__information.html</anchorfile>
      <anchor>aa8deb112b162419ef496259d8c07e692</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_user_information *</type>
      <name>requested_by</name>
      <anchorfile>d5/d06/structbfcp__floor__request__information.html</anchorfile>
      <anchor>a5daa6db34fe4142b6a4d0bd1c43fd744</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_priority</type>
      <name>priority</name>
      <anchorfile>d5/d06/structbfcp__floor__request__information.html</anchorfile>
      <anchor>a60f92cba0c5499347374bd5ce558c88b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>pInfo</name>
      <anchorfile>d5/d06/structbfcp__floor__request__information.html</anchorfile>
      <anchor>a86024e7b0e8770a4d1c32a43fbfe8685</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_floor_request_information *</type>
      <name>next</name>
      <anchorfile>d5/d06/structbfcp__floor__request__information.html</anchorfile>
      <anchor>aa38f097c03172ae74d71d591effb7ef9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_floor_request_status</name>
    <filename>d7/d8d/structbfcp__floor__request__status.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>fID</name>
      <anchorfile>d7/d8d/structbfcp__floor__request__status.html</anchorfile>
      <anchor>a3e549b3bd670c3fc4f2bcb640e588da2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_request_status *</type>
      <name>rs</name>
      <anchorfile>d7/d8d/structbfcp__floor__request__status.html</anchorfile>
      <anchor>ae021d8c738ab4bc85933e9d4c58f6ed6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>sInfo</name>
      <anchorfile>d7/d8d/structbfcp__floor__request__status.html</anchorfile>
      <anchor>a4766fbf3d5dcba4422a46d6742c6b668</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_floor_request_status *</type>
      <name>next</name>
      <anchorfile>d7/d8d/structbfcp__floor__request__status.html</anchorfile>
      <anchor>a9b1abdb11ab330febd47dd32725fc057</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_floors</name>
    <filename>d7/d27/structbfcp__floors.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>floorID</name>
      <anchorfile>d7/d27/structbfcp__floors.html</anchorfile>
      <anchor>a928f2816a6a54439fab7d5537ed5b958</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>chairID</name>
      <anchorfile>d7/d27/structbfcp__floors.html</anchorfile>
      <anchor>ace2f773c0cae1e98c990491fd68f52cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_floor_state</type>
      <name>floorState</name>
      <anchorfile>d7/d27/structbfcp__floors.html</anchorfile>
      <anchor>a766ee0b8e4683c9bee2ac69be6c15233</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>limit_granted_floor</name>
      <anchorfile>d7/d27/structbfcp__floors.html</anchorfile>
      <anchor>acbe133718dbf05ac9ad33b260782371a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct floor_query *</type>
      <name>floorquery</name>
      <anchorfile>d7/d27/structbfcp__floors.html</anchorfile>
      <anchor>a6c75de96ff3c07e848bc6696ea159463</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_floors_participant</name>
    <filename>de/d18/structbfcp__floors__participant.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>floorID</name>
      <anchorfile>de/d18/structbfcp__floors__participant.html</anchorfile>
      <anchor>ae9eb4a774445b83c2994745d5179b7be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>sInfo</name>
      <anchorfile>de/d18/structbfcp__floors__participant.html</anchorfile>
      <anchor>a8613f16a93b83953cc68b7062a3acaa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_floors_participant *</type>
      <name>next</name>
      <anchorfile>de/d18/structbfcp__floors__participant.html</anchorfile>
      <anchor>a9364e6906486245a74b5f9806559cc10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCP_fsm</name>
    <filename>dc/dfb/classBFCP__fsm.html</filename>
    <class kind="struct">BFCP_fsm::st_BFCP_fsm</class>
    <class kind="struct">BFCP_fsm::st_BFCP_fsm_event</class>
    <member kind="enumeration">
      <type></type>
      <name>e_BFCP_ACT</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_UNDEFINED</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00ac55f5f9fe08421e8bc623081927dea1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_INITIALIZED</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00ad1b9f7fbc1d4ebbb4d2417dd10076560</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_DISCONNECTED</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00ad6ae7ef8a777b4ec2d4df45df7347cfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_CONNECTED</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00af4903705f1fb6a328257245fb6c15d84</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorRequest</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00aff187cc770dd5ffb414b846372ee2d7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorRelease</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a08b726568d996d0fb6dcbfc01f078a0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorRequestQuery</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a2dc9b9fa6f943bdbe0c3d1b5df5cf3e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_UserQuery</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a166ad61c9416ea02e356096febeeefe0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorQuery</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a5ed0a0f61033905337555c6129279943</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_ChairAction</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a6b8eb5603f772a0684687633e681caf5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_Hello</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a27fdf03004ed2f3737cd90ce07fd304b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_Error</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a871fa4c2cbd18018f3df179f7d7b359c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorRequestStatusAccepted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00ab88c711a77c684dfcdc8c65abcc8df71</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorRequestStatusAborted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a074bab59334120106dd1845d43b2d396</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorRequestStatusGranted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a5945798cf8a9e2fcdbad79f561d7d538</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_UserStatus</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a505db67aeee8db96fc322192e322e475</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorStatusAccepted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a9704e8e038db5b7e1d0253d649c8caba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorStatusAborted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a6cf9c4279a2b63af3e07c5689cb6d5d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_FloorStatusGranted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00aef0f4f7aa409f28d5c91b73df56c2b19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_ChairActionAck</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00ac024a39b73acbf984e6e9aa2923bef33</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_HelloAck</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a8211d164ddb5f6ccbd211dfa57bd9453</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_SHARE</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a001ce2b607194025f68d5bb9fc781ac0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_SERVER_SHARE</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00a5c5acf968908ef122246ad84e9e5057f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BFCP_ACT_LAST</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a51eb496624d4c646758da34f45056a00aec1adec00435ba118c26034bc9125370</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCP_fsm</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>ae2babaea2d7be582f833f05ede6a85ef</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BFCP_fsm</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a4569c53c99cd8bcebbd6131ca4200b58</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>e_BFCP_ACT</type>
      <name>GetFSMState</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a6bca3c50ba31780651aa492fcd3c2686</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>FsmCtrlPerform</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>adb31e9e3f862c3892496be513080c5c0</anchor>
      <arglist>(e_BFCP_ACT p_evt, s_bfcp_msg_event *p_param=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a74ec9e14e561b7839ce3e3af806afc9c</anchor>
      <arglist>(const char *p_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FsmEvent</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a4eb3bb5cb6d6a5592eb9d7453105fafc</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Log</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>aa4b4e9cf63606b214cd386dbf5276f3d</anchor>
      <arglist>(const char *pcFile, int iLine, int iErrorLevel, const char *pcFormat,...)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>BFCPFSM_init</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a041ceafaf8867b83982ad94f62d5acfc</anchor>
      <arglist>(st_BFCP_fsm BFCPStateMachine[BFCP_ACT_LAST][BFCP_ACT_LAST])</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_NullFunction</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a24af38a810be301a2d1d0916a044ffaf</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_Connected</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>ae3cb6ab10eab28268772381741beb214</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_Disconnected</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a99cebb5b5d539592c2ea16884687e0d1</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorStatusAccepted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a373b4260f209772f8119cd6b0e47726d</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorStatusGranted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>ad4fa122a1d805c756b5d7e3d5d733cec</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorStatusAborted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a0e5542e3e4bf57272d9b96e0dc76b663</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRequestStatusAccepted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a8b99d8b835234379c49b5a2dd1c8390f</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRequestStatusGranted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>af0af4c63af097f36dbd1ca28c4563c3d</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRequestStatusAborted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a36b28408366ed1049602e3cd530d5b1d</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorReleaseStatusAborted</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a2ec8580c471539c4359f77e9c9667f6d</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRelease</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a9909e060cc0e842df1a444133da715de</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRequest</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a9b4569a06854c61150d35a5a1316ce3f</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_UpdateHwnd</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>abf9f881cea1bf9791bf9bbeb194fdd0d</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_Hello</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>aa89a5d594adb872414c9e8545b99f85c</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_HelloAck</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>af5efd7bbd776ebd3dfa0c2ae110c0930</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_PrimitiveNotSupported</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>aecb608d52aabd1e112daacb5bd42e1be</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_UpdatesBfcpFsmEvent</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a35c3a12f3eb313217beec78a701fb966</anchor>
      <arglist>(s_bfcp_msg_event *p_bfcp_evt, e_BFCP_ACT p_evt, e_BFCP_ACT p_st)</arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>bool(BFCP_fsm::*</type>
      <name>tBFCP_fsm_function</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>af2311d8b59e4bea36dc8815746f62392</anchor>
      <arglist>)(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>st_BFCP_fsm</type>
      <name>m_BFCPStateMachine</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a2bfac5123d85239890618eac3f4aa542</anchor>
      <arglist>[BFCP_ACT_LAST][BFCP_ACT_LAST]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>e_BFCP_ACT</type>
      <name>m_bfcpFsmSt</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>a81b4633cb300fdb1197c55a4334efb1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>char</type>
      <name>m_name</name>
      <anchorfile>dc/dfb/classBFCP__fsm.html</anchorfile>
      <anchor>aacb952c7169750e1202d44f596fafb09</anchor>
      <arglist>[BFCP_STRING_SIZE]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>BFCP_fsm::st_BFCP_fsm</name>
    <filename>dd/d88/structBFCP__fsm_1_1st__BFCP__fsm.html</filename>
    <member kind="variable">
      <type>e_BFCP_ACT</type>
      <name>new_state</name>
      <anchorfile>dd/d88/structBFCP__fsm_1_1st__BFCP__fsm.html</anchorfile>
      <anchor>a65bbebfb9bf2da5d5c735b4e1a8ff7a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>tBFCP_fsm_function</type>
      <name>function</name>
      <anchorfile>dd/d88/structBFCP__fsm_1_1st__BFCP__fsm.html</anchorfile>
      <anchor>aa28198d239fbad09906d282d3e58a111</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>BFCP_fsm::st_BFCP_fsm_event</name>
    <filename>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</filename>
    <member kind="variable">
      <type>e_BFCP_ACT</type>
      <name>State</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>a00249309303b2e952bd11104f3c12647</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>TransactionID</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>af41ee6086fe41522cc512190907ad554</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>userID</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>add2882208b7771d2a870d5b0e514db5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT32</type>
      <name>conferenceID</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>a3ce92a767de733b5deb6484e4f74f54e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>FloorID</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>aa6874092a5629b77b0e8844b6c0fbb58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>FloorRequestID</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>ae7c6d54bf91b4aa3cb5105baef50def8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>QueuePosition</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>a39abd3a7e8058745ba26181a6c5b00f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>BeneficiaryID</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>a26676e42d6cc3e421784b54c0e0ed797</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>i_parm</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>aa3df87dfd5a6d2cfaae7e7a6d365dc1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>c_param</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>aec44901ce9488249f231f417592f6e97</anchor>
      <arglist>[BFCP_STRING_SIZE]</arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>pt_param</name>
      <anchorfile>d9/dec/structBFCP__fsm_1_1st__BFCP__fsm__event.html</anchorfile>
      <anchor>ac99565d3ad19e8e0a27f45fc9fb7dfb9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCP_LinkList</name>
    <filename>d1/d62/classBFCP__LinkList.html</filename>
    <member kind="function">
      <type></type>
      <name>BFCP_LinkList</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>ac0a40628b469d2a2dbb2724828a29e33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BFCP_LinkList</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a491d634f319d22096e89c4fefc15db65</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bfcp_user_information *</type>
      <name>BFCP_LinkList_show_user_information</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>acee9b6467eda55f3c01882870a06c069</anchor>
      <arglist>(lusers list_users, UINT16 userID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Log</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a31ab83535a26f758636a10b376b58e69</anchor>
      <arglist>(const char *pcFile, int iLine, int iErrorLevel, const char *pcFormat,...)=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>struct bfcp_queue *</type>
      <name>bfcp_create_list</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>affb16a813264fcd6c14dbe415e686a66</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>struct bfcp_node *</type>
      <name>bfcp_init_request</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>ae52c379c5a6e9fc97cf4b3d6b93e07a3</anchor>
      <arglist>(UINT16 userID, UINT16 beneficiaryID, e_bfcp_priority priority, char *text, UINT16 floorID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_add_floor_to_request</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a95f94748e63f77539a7045f4cc6946b4</anchor>
      <arglist>(pnode newnode, UINT16 floorID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_insert_request</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a3f3367c5d811e04ca49ceae857cb4a17</anchor>
      <arglist>(bfcp_queue *conference, pnode newnode, UINT16 floorRequestID, char *chair_info)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>UINT16</type>
      <name>bfcp_give_user_of_request</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a70bda06f7f02d07d2692ea06912204d4</anchor>
      <arglist>(bfcp_queue *conference, UINT16 floorRequestID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_change_status</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>ab2a0f2b0b767759ef8bbba67a5e87b3a</anchor>
      <arglist>(bfcp_queue *conference, UINT16 floorID, UINT16 floorRequestID, e_floor_state status, char *floor_chair_info)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_all_floor_status</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a60a046c75da410fdaf668bb94c04625a</anchor>
      <arglist>(bfcp_queue *conference, UINT16 floorRequestID, e_floor_state status)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_all_floor_pID</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a9bdfe8682e3b7760f3ae880c08da5621</anchor>
      <arglist>(pnode newnode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_delete_node_with_floorID</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a3f7b3d089e0ffd1de8fa6c9ed33f091b</anchor>
      <arglist>(UINT32 conferenceID, bfcp_queue *accepted, bfcp_queue *conference, UINT16 floorID, bfcp_list_floors *lfloors, int type_list)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_delete_node_with_userID</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a2760ed53064ebdd2bea81ee4d7005502</anchor>
      <arglist>(bfcp_queue *conference, UINT16 userID, bfcp_list_floors *lfloors)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bfcp_floor *</type>
      <name>bfcp_delete_request</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a093073d4069e8f26b1d6575ca65aff19</anchor>
      <arglist>(bfcp_queue *conference, UINT16 floorRequestID, int type_queue)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bfcp_node *</type>
      <name>bfcp_extract_request</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a88fa248c0846b2c146259f4d39eee7e7</anchor>
      <arglist>(bfcp_queue *conference, UINT16 floorRequestID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_floor_request_query_server</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>ac795578ae49b78215c77a21fdc627370</anchor>
      <arglist>(bfcp_queue *conference, UINT16 floorRequestID, UINT16 userID, int sockfd)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_clean_request_list</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a7fc13038ae1bd69ea77d9d3a27ba5b45</anchor>
      <arglist>(bfcp_queue *conference)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_remove_request_list</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a283e54295030be5d27e9f3837bd1db26</anchor>
      <arglist>(bfcp_queue **conference)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_kill_threads_request_with_FloorRequestID</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>aeb866283a6e8259b2e7576644165d5d9</anchor>
      <arglist>(bfcp_queue *conference, UINT16 floorRequestID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bfcp_floor_request_information *</type>
      <name>bfcp_show_floorrequest_information</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>abf635f3bced1703867fe8441fd54929d</anchor>
      <arglist>(bfcp_queue *conference, lusers users, UINT32 FloorRequestID, int type_queue)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bfcp_floor *</type>
      <name>create_floor_list</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>aaa4fae122e3017333602ad262da25d44</anchor>
      <arglist>(UINT16 floorID, e_floor_state status, char *floor_chair_info)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bfcp_floor *</type>
      <name>add_floor_list</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a65578dd328922b59abc7168a56ebdd81</anchor>
      <arglist>(bfcp_floor *floor_list, UINT16 floorID, e_floor_state status, char *floor_chair_info)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>remove_floor_list</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>ab7dbbcd54b736e69dc442b9e2e549391</anchor>
      <arglist>(bfcp_floor *floor_list)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>remove_request_list_of_node</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a5e95bae9f90bec99bfe0444983c58379</anchor>
      <arglist>(floor_request_query *floorrequest)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>add_request_to_the_node</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a45819d84a97b8b5238856f1238cb145f</anchor>
      <arglist>(pnode traverse, UINT16 userID, int sockfd)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>remove_request_from_the_node</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>ac448619c9279ed8293faa69008e7d4a2</anchor>
      <arglist>(pnode traverse, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_accepted_pending_node_with_floorID</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a14a95138013747327d7c99f1d1901fbc</anchor>
      <arglist>(UINT32 conferenceID, bfcp_queue *accepted, bfcp_queue *conference, UINT16 floorID, bfcp_list_floors *lfloors, int type_list)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_change_queue_position</name>
      <anchorfile>d1/d62/classBFCP__LinkList.html</anchorfile>
      <anchor>a0210309d5e56b4f62568150348be1fd9</anchor>
      <arglist>(bfcp_queue *conference, UINT16 floorRequestID, UINT16 queue_position)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_list_floors</name>
    <filename>d8/dee/structbfcp__list__floors.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>number_floors</name>
      <anchorfile>d8/dee/structbfcp__list__floors.html</anchorfile>
      <anchor>ac45376013de0e2dd0af7368caad1a2d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>actual_number_floors</name>
      <anchorfile>d8/dee/structbfcp__list__floors.html</anchorfile>
      <anchor>a0e7791e54a24b177c52701006f55896d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_floors *</type>
      <name>floors</name>
      <anchorfile>d8/dee/structbfcp__list__floors.html</anchorfile>
      <anchor>aca9181d1353654ddb3be9344369fd74a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_list_users</name>
    <filename>df/d63/structbfcp__list__users.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>bfcp_transport</name>
      <anchorfile>df/d63/structbfcp__list__users.html</anchorfile>
      <anchor>a52fc6750fa668fa280f064487d41bfc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>max_number_floor_request</name>
      <anchorfile>df/d63/structbfcp__list__users.html</anchorfile>
      <anchor>aa6807b274dc432a47568902ad1dabdf8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>maxnumberfloors</name>
      <anchorfile>df/d63/structbfcp__list__users.html</anchorfile>
      <anchor>aef6e5aeb11ab48ac05aa99565ef00d89</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_user *</type>
      <name>users</name>
      <anchorfile>df/d63/structbfcp__list__users.html</anchorfile>
      <anchor>a1a140aeabe6a655deb7f19dcb0e796ca</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_message</name>
    <filename>dc/d50/structbfcp__message.html</filename>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>buffer</name>
      <anchorfile>dc/d50/structbfcp__message.html</anchorfile>
      <anchor>af6ff58e21fde913dad3e727588985624</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>position</name>
      <anchorfile>dc/d50/structbfcp__message.html</anchorfile>
      <anchor>ac29cb3b5b93bc184a3410f1cc68a4d1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>length</name>
      <anchorfile>dc/d50/structbfcp__message.html</anchorfile>
      <anchor>a7176c195523c8c8ea046c3f8ecef258f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_node</name>
    <filename>d8/dda/structbfcp__node.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>floorRequestID</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>a9a045761611af0fd865fff21700a11d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>userID</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>abcf62990ecf7991d9da398cb2bc1541c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>beneficiaryID</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>a17c8eaf77a7ac9489f0b820bbcc53a69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_priority</type>
      <name>priority</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>a591730d7b429b390965cecc2465b962e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>queue_position</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>aec4bba0df2156141a0452123d6eb6ae5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>participant_info</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>a8d8d0e2f783107053f2e7e6c82a7a65a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>chair_info</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>a9f4463426f5b41c04beead757ab33404</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct floor_request_query *</type>
      <name>floorrequest</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>a1cd44f5e017f324207da7889dc797e10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_floor *</type>
      <name>floor</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>ac4a40a56c2e83c4f8ac6c524266baacf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_node *</type>
      <name>next</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>a492adc526e72bcbf17662e472d9398b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_node *</type>
      <name>prev</name>
      <anchorfile>d8/dda/structbfcp__node.html</anchorfile>
      <anchor>adfb32fa089386092eee17aeb30903c17</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_overall_request_status</name>
    <filename>dd/d01/structbfcp__overall__request__status.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>frqID</name>
      <anchorfile>dd/d01/structbfcp__overall__request__status.html</anchorfile>
      <anchor>a544a62398f4ee5a5c7ca13ab81cf692c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_request_status *</type>
      <name>rs</name>
      <anchorfile>dd/d01/structbfcp__overall__request__status.html</anchorfile>
      <anchor>a7f4c531b577602c260fe6e0222a0dac4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>sInfo</name>
      <anchorfile>dd/d01/structbfcp__overall__request__status.html</anchorfile>
      <anchor>aae4a73250d18309f7ce50005d17e678e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCP_Participant</name>
    <filename>d0/d04/classBFCP__Participant.html</filename>
    <base>BFCPConnection</base>
    <base>BFCP_fsm</base>
    <class kind="class">BFCP_Participant::ParticipantEvent</class>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Log</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a57748ec8db89389aaff97c8082d73c67</anchor>
      <arglist>(const char *pcFile, int iLine, int iErrorLevel, const char *pcFormat,...)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BFCP_Participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a80d03ee351ca64758d6ba3cfb39a95f5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCP_Participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>ab78422a034991c599a9b11a5173d29d9</anchor>
      <arglist>(UINT32 p_confID, UINT16 p_userID, UINT16 p_floorID, UINT16 p_streamID, BFCP_Participant::ParticipantEvent *p_ParticipantEvent)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>OpenTcpConnection</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a2837a81ea8ab6fdb87bb03e34b40f275</anchor>
      <arglist>(const char *local_address, int local_port, const char *remote_address, int remote_port, bool isServer)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>CloseTcpConnection</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a7cfad9996bf8d1cf3fa9004b6e05124a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkFloorRequestID</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a463b7e9287556e26dd307a13c51d1932</anchor>
      <arglist>(UINT16 p_FloorRequestID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_floorRequest_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>ac7ab095004b431092856141a68cb706d</anchor>
      <arglist>(UINT16 p_floorID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_floorRelease_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>ac57df778daf4e037482b4bd1dc66aed5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>st_bfcp_participant_information *</type>
      <name>GetCurrentParticpantInfo</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>abff7a927c7882abbbac5e68aa7f49398</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_hello_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a1b3b33e5d236d635c69c99e58a2b3509</anchor>
      <arglist>(st_bfcp_participant_information *participant)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_floorRequest_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a2a01a7987f4b8367d3b571d078040534</anchor>
      <arglist>(st_bfcp_participant_information *participant, UINT16 beneficiaryID, e_bfcp_priority priority, bfcp_floors_participant *list_floors, char *participant_info)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_floorRelease_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a29bf403c916d1836c78f02ae7bc9b2bc</anchor>
      <arglist>(st_bfcp_participant_information *participant, UINT16 floorRequestID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_floorRequestQuery_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a7cfbe1c1dc75bf2c244e795513e9fce8</anchor>
      <arglist>(st_bfcp_participant_information *participant, UINT16 floorRequestID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_userQuery_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a6d4da2c3a3acc1371a024b99d00c96f5</anchor>
      <arglist>(st_bfcp_participant_information *participant, UINT16 beneficiaryID)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_floorQuery_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a1bcc0635db6b65bf74bc959ac4d23681</anchor>
      <arglist>(st_bfcp_participant_information *participant, bfcp_floors_participant *list_floors)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>bfcp_chairAction_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>adc74cfc158ff19bc30243353fa4cae26</anchor>
      <arglist>(st_bfcp_participant_information *participant, UINT16 floorRequestID, char *statusInfo, UINT16 status, bfcp_floors_participant *list_floors, UINT16 queue_position)</arglist>
    </member>
    <member kind="function">
      <type>st_bfcp_floors_participant *</type>
      <name>create_floor_list</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>ad369e5a9effa980d587dc8ad8774f1ad</anchor>
      <arglist>(UINT16 floorID, char *status_info)</arglist>
    </member>
    <member kind="function">
      <type>st_bfcp_floors_participant *</type>
      <name>insert_floor_list</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a60c8a71f804b493a14c2da7091b9c8b3</anchor>
      <arglist>(st_bfcp_floors_participant *floor_list, UINT16 floorID, char *status_info)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>remove_floor_list</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>ace2c0bb6a1fcd6c234c2fe27f2377b77</anchor>
      <arglist>(st_bfcp_floors_participant *floor_list)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCP_Participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a72c78c449f9c7a3efa7d1b3621ee948e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCPConnection</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a5c25361dfe09ab40bd1af191d42a5062</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BFCPConnection</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a29050affb6a4ea525eb2702fcdfe119d</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isConnected</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a38123dee72938ea1a1b62d8d8e24380c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isStarted</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>abc6be88ffc31c8eaad75866db537a228</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SelLocalConnection</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a8b09f0fd896a5247a28c116c34e6633a</anchor>
      <arglist>(const char *localAddress, UINT16 port, int eRole)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getLocalAdress</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a8a75725759038accdb8bad6289a81c3a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>getLocalPort</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a671c819c654025c0a1c71cfd32225b03</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getRemoteAdress</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a444974e8d670ee4e6536b50af9fc072c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>getRemotePort</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a988e1b45b489d664e878bf50e76e2197</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setRemoteEndpoint</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a31abc84f9f2aeaaa5e454dc2b5382f55</anchor>
      <arglist>(const char *address, UINT16 port)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addSession</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a8e215e14b180c3fde5334ce8693957e0</anchor>
      <arglist>(const std::string &amp;sessionId)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeSession</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a157c5e8daf483ddb30f32fcc5c17825a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sendBFCPmessage</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a926065c0bbbf84c30679b90237ecfc67</anchor>
      <arglist>(BFCP_SOCKET client_sock, bfcp_message *message)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>BFCPconnect</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a45f41c978feb8dd631584d34c1097992</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>aa2a1b81d7c6a671c593031acd870050c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BFCP_SOCKET</type>
      <name>getServerSocket</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>ac8070d2f14b0ff71342c13c6084f92fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bfcp_message *</type>
      <name>readAndProcessBFCPmessage</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>acb17fe09cedb890712aca8bc97bb8092</anchor>
      <arglist>(BFCP_SOCKET p_sock)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>OnBFCPConnected</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a82f3a5c7deaf9ed8cb04177d25456094</anchor>
      <arglist>(BFCP_SOCKET socket, char *RemoteIp, int remotePort)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>OnBFCPDisconnected</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a074a67920cc677db2806a2b7a2c2ce01</anchor>
      <arglist>(BFCP_SOCKET socket, char *RemoteIp, int remotePort)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_Connected</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a74938d676315a08a502ab8d9912f2c7a</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_Disconnected</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a8bf9d2874b5219f404d478acf6cc8ac3</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorStatusAccepted</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a2e129ce647e3499a70582fe6a88ef49a</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorStatusGranted</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a7ebf50591b12f947b8383650827fb1b3</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorStatusAborted</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a65e26e6e6416aceaf8234d1e7c96a3c0</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRequestStatusAccepted</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>ad4d39e961447df667473eea7374c4214</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRequestStatusGranted</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a8ec7d46efcb93ceab59dd2ea6a4be628</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRequestStatusAborted</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a885f75502abe7742bf474618c35b23c2</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorReleaseStatusAborted</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>ad62a331821605d4f7ff0d6a54b8dc162</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRelease</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a5b4ebe8ab96de59ab9f28ffc16958699</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRequest</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a37ce120d34e9409bcde0639964a88db9</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_UpdateHwnd</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a9e70ab75a907bdfe51900ce2fe91f056</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_UpdatesBfcpFsmEvent</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a6315748727799209a7b9a33238123ac4</anchor>
      <arglist>(s_bfcp_msg_event *p_bfcp_evt, e_BFCP_ACT p_evt, e_BFCP_ACT p_st)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>bfcp_received_msg</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>af8de350e665f3e662bbb74ea153dede7</anchor>
      <arglist>(bfcp_received_message *recv_msg)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_destroy_bfcp_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>af54c296b7bd5f89809fdfd6554297b9b</anchor>
      <arglist>(st_bfcp_participant_information **participant)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_insert_floor_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>aad6a0977025842d2ed6f18393ebbcb18</anchor>
      <arglist>(st_bfcp_participant_information *participant, UINT16 floorID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_delete_floor_participant</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a8cbcd313100aa7bc1a62a28c6cd6fc54</anchor>
      <arglist>(st_bfcp_participant_information *participant, UINT16 floorID)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_base_transactionID</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a099a17c2e67f9a98e9d1dd835b4ac004</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_bfcp_transport</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a30c438963600f285a6f025344a7b371a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>st_bfcp_participant_information *</type>
      <name>m_bfcp_participant_information</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>aa9fbe70fe9ef63e2a1635a38255c5a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_currentFloorRequestID</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a547153cb454d4803729b35de85c7543d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bfcp_mutex_t</type>
      <name>count_mutex</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a7e57cf5e508aec0e28a0fe1082d63f0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ParticipantEvent *</type>
      <name>m_ParticipantEvent</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>a133e045e8fb2fc2df5a996dd86786621</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BFCP_SOCKET</type>
      <name>m_PartSocket</name>
      <anchorfile>d0/d04/classBFCP__Participant.html</anchorfile>
      <anchor>ad1b091967f7ab32d7baf039cbf37ee6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static bool</type>
      <name>GetSockinfo</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a3baecb84b9acb1202f5a5c831cb85320</anchor>
      <arglist>(BFCP_SOCKET sock, char *localIp, int *localPort, char *remoteIp, int *remotePort)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void *</type>
      <name>EntryPoint</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a103b8dca53525eb59982f27bbfc27c65</anchor>
      <arglist>(void *pParam)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCP_Participant::ParticipantEvent</name>
    <filename>d8/d28/classBFCP__Participant_1_1ParticipantEvent.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>OnBfcpParticipantEvent</name>
      <anchorfile>d8/d28/classBFCP__Participant_1_1ParticipantEvent.html</anchorfile>
      <anchor>a2273c80d15f0e54669b7c39a9dd78ddf</anchor>
      <arglist>(e_BFCP_ACT p_evt, st_BFCP_fsm_event *p_FsmEvent)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ParticipantEvent</name>
      <anchorfile>d8/d28/classBFCP__Participant_1_1ParticipantEvent.html</anchorfile>
      <anchor>a7075c404f42018c1c1452807afd70e3e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_queue</name>
    <filename>dd/d41/structbfcp__queue.html</filename>
    <member kind="variable">
      <type>pnode</type>
      <name>head</name>
      <anchorfile>dd/d41/structbfcp__queue.html</anchorfile>
      <anchor>af3052236e43d5d1de976dd86004ab78c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>pnode</type>
      <name>tail</name>
      <anchorfile>dd/d41/structbfcp__queue.html</anchorfile>
      <anchor>a6d6e731408d925a9fdf6ebb4cdef876e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_received_attribute</name>
    <filename>d1/dbc/structbfcp__received__attribute.html</filename>
    <member kind="variable">
      <type>e_bfcp_attibutes</type>
      <name>type</name>
      <anchorfile>d1/dbc/structbfcp__received__attribute.html</anchorfile>
      <anchor>aafedf5d13e539e0dc4742fa98e8967d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>mandatory_bit</name>
      <anchorfile>d1/dbc/structbfcp__received__attribute.html</anchorfile>
      <anchor>a61fd62bfb60760eedb8813e6e8da8671</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>length</name>
      <anchorfile>d1/dbc/structbfcp__received__attribute.html</anchorfile>
      <anchor>a0a38dc5e7512917e3de4d4d62463e8e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>position</name>
      <anchorfile>d1/dbc/structbfcp__received__attribute.html</anchorfile>
      <anchor>a0ff095d5371545b88097052d20a890c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>valid</name>
      <anchorfile>d1/dbc/structbfcp__received__attribute.html</anchorfile>
      <anchor>a3d340993f36b5896389d7a1029b4ad9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_received_attribute *</type>
      <name>next</name>
      <anchorfile>d1/dbc/structbfcp__received__attribute.html</anchorfile>
      <anchor>abebb2175ea859aed09f216ddaaa19701</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_received_message</name>
    <filename>d6/d8e/structbfcp__received__message.html</filename>
    <member kind="variable">
      <type>bfcp_arguments *</type>
      <name>arguments</name>
      <anchorfile>d6/d8e/structbfcp__received__message.html</anchorfile>
      <anchor>af1495c8f954e2f4ab541baf0d8c35c8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>version</name>
      <anchorfile>d6/d8e/structbfcp__received__message.html</anchorfile>
      <anchor>a26e75aa05633c680a4c7f2b1d5bcbb8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>reserved</name>
      <anchorfile>d6/d8e/structbfcp__received__message.html</anchorfile>
      <anchor>ab99291926c512d3b065000ca06cc71bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_primitives</type>
      <name>primitive</name>
      <anchorfile>d6/d8e/structbfcp__received__message.html</anchorfile>
      <anchor>a3309fd902601cafa542800573aff89c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>length</name>
      <anchorfile>d6/d8e/structbfcp__received__message.html</anchorfile>
      <anchor>aa14586035855de67c646f89be8fdebac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_entity *</type>
      <name>entity</name>
      <anchorfile>d6/d8e/structbfcp__received__message.html</anchorfile>
      <anchor>ae1954c2d14b8248fc97e2857131eae5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_received_attribute *</type>
      <name>first_attribute</name>
      <anchorfile>d6/d8e/structbfcp__received__message.html</anchorfile>
      <anchor>af91ac90a909c3dc27a529aee7d24f1d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_received_message_error *</type>
      <name>errors</name>
      <anchorfile>d6/d8e/structbfcp__received__message.html</anchorfile>
      <anchor>aac86032007a87c797fc5e5c129160a8a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_received_message_error</name>
    <filename>d1/d11/structbfcp__received__message__error.html</filename>
    <member kind="variable">
      <type>e_bfcp_primitives</type>
      <name>attribute</name>
      <anchorfile>d1/d11/structbfcp__received__message__error.html</anchorfile>
      <anchor>adf762273b2dcd9d84fee1635bab4a583</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_error_codes</type>
      <name>code</name>
      <anchorfile>d1/d11/structbfcp__received__message__error.html</anchorfile>
      <anchor>a8f210b68a5c0e8559cbe9e74625d3d85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_received_message_error *</type>
      <name>next</name>
      <anchorfile>d1/d11/structbfcp__received__message__error.html</anchorfile>
      <anchor>ac265501977e3c10019aea6bfa6cc4f27</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_request_status</name>
    <filename>d4/d40/structbfcp__request__status.html</filename>
    <member kind="variable">
      <type>e_bfcp_status</type>
      <name>rs</name>
      <anchorfile>d4/d40/structbfcp__request__status.html</anchorfile>
      <anchor>a80586314ef70842ad80d5f071f88f72d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT8</type>
      <name>qp</name>
      <anchorfile>d4/d40/structbfcp__request__status.html</anchorfile>
      <anchor>a527f541459c57d44a41a9602d06c8ef2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCP_Server</name>
    <filename>d3/dd0/classBFCP__Server.html</filename>
    <base>BFCPConnection</base>
    <base>BFCP_fsm</base>
    <base>BFCP_LinkList</base>
    <base>BFCP_UserList</base>
    <class kind="class">BFCP_Server::ServerEvent</class>
    <member kind="function">
      <type></type>
      <name>~BFCP_Server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>acb813ad77c27cd2ca7654884e15ddd6b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCP_Server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ae40dcf99600bdada5ae7b3304ef9a8bd</anchor>
      <arglist>(UINT8 Max_conf, UINT32 p_confID, UINT32 p_userID, UINT32 p_floorID, UINT32 p_streamID, BFCP_Server::ServerEvent *p_ServerEvent)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>OpenTcpConnection</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>abf82345bd7ad85e7621f8364a9db0687</anchor>
      <arglist>(const char *local_address, int local_port, const char *remote_address, int remote_port, bool isServer)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>CloseTcpConnection</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a4febc3030a9a9ffd2175e2eca747562c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Log</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aff470ced32a86576e4b116d45d146f5e</anchor>
      <arglist>(const char *pcFile, int iLine, int iErrorLevel, const char *pcFormat,...)</arglist>
    </member>
    <member kind="function">
      <type>UINT32</type>
      <name>GetConfID</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a31355178a9fab9fe482fbfa970d1cc39</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetFirstUserID</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aa85b38fa0488884a9139f05e29f8eb45</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetFloorID</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ad0322a666ae1faf2081c7406baccfa53</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetStreamID</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a1539a01f5437cac5f97a1790e3c3ac64</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isUserInConf</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a35183cf0f1e09eb0eaac586bb5202591</anchor>
      <arglist>(UINT16 userID)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddUser</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a7dbfc5cf15bb5572b55cdb9ad497f939</anchor>
      <arglist>(UINT16 userID, char *user_URI=NULL, char *user_display_name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RemoveUserInConf</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a2aaeb8b1bfe37e92fcda6802ec0f4a06</anchor>
      <arglist>(UINT16 userID)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DumpServer</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a8a913d54712d98000708a00d6ea47719</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>FloorRequestRespons</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a9eaf390bcc193fe773c0310035eade0f</anchor>
      <arglist>(UINT32 p_userID, UINT32 p_beneficiaryID, UINT16 p_TransactionID, UINT16 p_floorRequestID, e_bfcp_status p_bfcp_status, UINT16 p_queue_position=0, e_bfcp_priority p_priority=BFCP_NORMAL_PRIORITY, bool p_InformALL=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SendFloorStatus</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a40f70e19b16a15ef3e23c972c5bf0504</anchor>
      <arglist>(UINT32 p_userID, UINT16 p_TransactionID, UINT16 p_floorRequestID, bfcp_node *node, bool p_InformALL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetFloorState</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a0a392de389bf168adda8bb9bce6a286d</anchor>
      <arglist>(e_bfcp_status *p_bfcp_status, UINT32 *p_userID, UINT32 *p_beneficiaryID, UINT16 *p_floorRequestID)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCP_Server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a4d8d5137f7f337d6b72a3c0c41c4c52a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCP_UserList</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a167919b31efd36c3cbbe87c7d1e8e9eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BFCP_UserList</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a59c367b964dddfa625e7fffc687e13a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bfcp_message *</type>
      <name>readAndProcessBFCPmessage</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a3b6c63ecb80978841ed82259f5608111</anchor>
      <arglist>(BFCP_SOCKET p_sock)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>OnBFCPConnected</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a3c6e2f9a032f6b930d6c2d9eec1f863e</anchor>
      <arglist>(BFCP_SOCKET socket, char *RemoteIp, int remotePort)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>OnBFCPDisconnected</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a51aa91fbee12d54af00bbf571b1099d3</anchor>
      <arglist>(BFCP_SOCKET socket, char *RemoteIp, int remotePort)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual int</type>
      <name>BFCP_UserList_error_code</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a4ffee05069f22de9d1d373c61dee7486</anchor>
      <arglist>(UINT32 conferenceID, UINT16 userID, UINT16 TransactionID, e_bfcp_error_codes code, char *error_info, bfcp_unknown_m_error_details *details, int sockfd, int i, int transport)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bfcp_user_information *</type>
      <name>BFCP_LinkList_show_user_information</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aa90d9de65ce48d1975ed7a56bbd34814</anchor>
      <arglist>(lusers list_users, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>BFCPFSM_UpdatesBfcpFsmEvent</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>af5e830ee240bfc3353944a68853f071b</anchor>
      <arglist>(s_bfcp_msg_event *p_bfcp_evt, e_BFCP_ACT p_evt, e_BFCP_ACT p_st)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_Hello</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aa682e74fc97f9fe1ec380dafef4624d8</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_PrimitiveNotSupported</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a1de5dbead8b64f25a453c16f0222b9b9</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRelease</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a9a82c10ecd1dd4c9b8a1712177f442cf</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>BFCPFSM_FloorRequest</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>afd543e8b37caf74ff4abb211023f59be</anchor>
      <arglist>(s_bfcp_msg_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>struct bfcp_list_users *</type>
      <name>bfcp_create_user_list</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>aee767b2ab06f68687d9a0ecf9f59aad4</anchor>
      <arglist>(UINT16 Max_Number_Floor_Request, UINT16 Num_floors)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_existence_user</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>aceaa4b7386574223103c83d5c0922245</anchor>
      <arglist>(lusers list_users, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_change_user_req_floors</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a0ed45631a6096c66ab892feefc4c0f80</anchor>
      <arglist>(lusers list_users, UINT16 Max_Number_Floor_Request)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_change_number_users_floors</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a1651b0333555de8df51a502318deb387</anchor>
      <arglist>(lusers list_users, UINT16 Num_floors)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_add_user</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a07ebf869c9e7e8dae45f92a212003e95</anchor>
      <arglist>(lusers list_users, UINT16 userID, char *user_URI, char *user_display_name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_set_userSockFd</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a8de8790d0860503a2a9f1fdcfacab2a1</anchor>
      <arglist>(lusers list_users, UINT16 userID, BFCP_SOCKET p_sockfd)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>BFCP_SOCKET</type>
      <name>bfcp_get_userSockFd</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>aeb594a630b101ba7f8f00e9e0ff7bb37</anchor>
      <arglist>(lusers list_users, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_delete_user</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a64ff84ade057a447317b8b35dbec1300</anchor>
      <arglist>(lusers list_users, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_add_user_request</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a2b349a7710865489421a6566fe0a7b38</anchor>
      <arglist>(UINT32 ConferenceID, UINT16 TransactionID, lusers list_users, UINT16 userID, int position_floor, int sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_is_floor_request_full</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>ab2a3c95cb85db3db82a19c31a2aa533b</anchor>
      <arglist>(UINT32 ConferenceID, UINT16 TransactionID, lusers list_users, UINT16 userID, int position_floor, int sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_clean_all_users_request_of_a_floor</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>aba77b2874e0f05447a0648600a3b7236</anchor>
      <arglist>(lusers list_users, UINT16 floorID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_delete_a_floor_from_user_list</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a440b45330275de3cf1ca8fc4ec70b102</anchor>
      <arglist>(lusers list_users, UINT16 floorID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_deleted_user_request</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a7c7ed56fce11918a0d620c4e1daba68f</anchor>
      <arglist>(lusers list_users, UINT16 userID, int position_floor)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_clean_user_list</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>ab7267761191809535bb25867ded11b57</anchor>
      <arglist>(lusers list_users)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>bfcp_remove_user_list</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a6f5076c6d9f476430524d4b0d8ac64c5</anchor>
      <arglist>(bfcp_list_users **lusers_p)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bfcp_user_information *</type>
      <name>bfcp_show_user_information</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a1aa6d227e17b88cc915d51bb2697a828</anchor>
      <arglist>(lusers list_users, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>char *</type>
      <name>bfcp_obtain_userURI</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>a91d1da88dcba7e0250af836d790c23c3</anchor>
      <arglist>(lusers list_users, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>char *</type>
      <name>bfcp_obtain_user_display_name</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>aeb95bc0036c36f43ee7073334862d9e0</anchor>
      <arglist>(lusers list_users, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void *</type>
      <name>WatchDog</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a62dc072fc575cee306a68116b044b3e0</anchor>
      <arglist>(void *st_thread)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>initStateMachine</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a2cf1c54c4dec4e9916b49ccc3eb13b92</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>print_requests_list</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a19dc947602947452ac39c0507c3e30b8</anchor>
      <arglist>(st_bfcp_server *server, int index, e_bfcp_status status)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>FloorStatusRespons</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a31916257d6d23cd9bdc8184f01f09e2a</anchor>
      <arglist>(UINT32 p_userID, UINT16 p_TransactionID, UINT16 p_floorRequestID, bfcp_node *node, bool p_InformALL)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_destroy_bfcp_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a0fcc6d11061f18be962d87849a53f9af</anchor>
      <arglist>(st_bfcp_server **serverp)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_initialize_conference_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aab097e8ee0bc3cae9aaba65470979d79</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 Max_Num_Floors, UINT16 Max_Number_Floor_Request, int automatic_accepted_deny_policy, UINT32 chair_wait_request)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_destroy_conference_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a29d19f656e91ce9da0eecbed9000d15c</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_change_number_bfcp_conferences_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a56c802bc08284266e01cf646b57d0eac</anchor>
      <arglist>(st_bfcp_server *server, UINT16 Num)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_change_number_granted_floor_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a38f193ad33e7c146ac191f2f4f003c2a</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID, UINT16 limit_granted_floor)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_change_user_req_floors_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ab90f23e1ecc68740d46bc38467193c1b</anchor>
      <arglist>(st_bfcp_server *server, UINT16 Max_Number_Floor_Request)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_change_chair_policy</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ab43c31ff70c7a80777e71f634615c3b9</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, int automatic_accepted_deny_policy, UINT32 chair_wait_request)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_add_floor_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ab52a49e01ee393275380831b92ad1bd7</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID, UINT16 ChairID, int limit_granted_floor)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_delete_floor_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a2137762f873d8a1c5e853721d27c74c8</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_add_chair_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ae52638f68ca89e2a90bdc02fbb95c1b7</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID, UINT16 ChairID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_delete_chair_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a2174778900cfad4aad837b4c0cabc62f</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_add_user_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a12b25a2287613f8736f1944ef4bf0337</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 userID, char *user_URI, char *user_display_name)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_set_user_sockfd</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a180aca25d65c95abc650e8e524a38cb9</anchor>
      <arglist>(st_bfcp_server *server, UINT32 conferenceID, UINT16 userID, BFCP_SOCKET p_sockfd)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>BFCP_SOCKET</type>
      <name>bfcp_get_user_sockfd</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aa52af1152890ba2b979d29ff596292cb</anchor>
      <arglist>(st_bfcp_server *server, UINT32 conferenceID, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_delete_user_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ae5976c61de0d515c9446bf5a96560354</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bfcp_floor_request_information *</type>
      <name>create_floor_request_userID</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a7a3db4f327e1dc0f8543ff6271853e69</anchor>
      <arglist>(pnode traverse, lusers users, UINT16 userID, UINT16 request_status, int i)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bfcp_floor_request_information *</type>
      <name>create_floor_message</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a74d18549ef3a2564f4b8bea4258854dc</anchor>
      <arglist>(UINT16 floorID, pnode traverse, lusers users, UINT16 request_status, int i)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_print_information_floor</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ad55e5b511964f8228e6aeadec2be9029</anchor>
      <arglist>(st_bfcp_conference *conference, UINT16 userID, UINT16 TransactionID, pnode newnode, UINT16 status)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_show_requestfloor_information</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a104875dced7ecd28b690e0dcd46dfff5</anchor>
      <arglist>(bfcp_list_users *list_users, bfcp_queue *accepted_queue, UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID, pnode newnode, UINT16 status, BFCP_SOCKET socket)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_remove_floorrequest_from_all_nodes</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ab3b909f19b3924dabf12715557526915</anchor>
      <arglist>(st_bfcp_conference *server, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_remove_floorrequest_from_a_queue</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a793ebd7b3b6ebd537f48ae9d9c23053b</anchor>
      <arglist>(bfcp_queue *conference, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_remove_floorquery_from_all_nodes</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ad0c2f4087d8234107a7c087013e290e9</anchor>
      <arglist>(bfcp_list_floors *lfloors, UINT16 userID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_FloorRequest_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a49e361e512ec7411c164ef8c15531875</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 TransactionID, pnode newnode, int sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_FloorRelease_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a53183f012b2f345c7e2d473e2dc2c214</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 TransactionID, UINT16 userID, UINT16 FloorRequestID, BFCP_SOCKET sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_ChairAction_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a9909db3252ef759232df4152bdca8ee9</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, bfcp_floor *list_floors, UINT16 userID, UINT32 FloorRequestID, int RequestStatus, char *chair_info, UINT16 queue_position, UINT16 TransactionID, int sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_hello_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>abdff5663dd9a5013e239b38a7a439703</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID, BFCP_SOCKET sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_userquery_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aa982ffe7b35e53019ffeb4c5bf709504</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID, UINT16 beneficiaryID, BFCP_SOCKET sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_floorquery_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a49aba466205d0275bfb49368feb135c3</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, bfcp_floor *list_floors, UINT16 userID, UINT16 TransactionID, int sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_floor_query_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>acf5bd46ea7608014fa4b4df1ef123e1c</anchor>
      <arglist>(bfcp_list_floors *lfloors, bfcp_floor *list_floors, UINT16 userID, int sockfd)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_floorrequestquery_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a4a6d7956f4e1db131810027f3a43f627</anchor>
      <arglist>(st_bfcp_server *server, UINT32 ConferenceID, UINT16 TransactionID, UINT32 FloorRequestID, UINT16 userID, int sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>check_accepted_node</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aca71ecb440d4f1a5c65eef9168372efb</anchor>
      <arglist>(st_bfcp_conference *conference, pnode queue_accepted, UINT16 floorID, char *chair_info)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>give_free_floors_to_the_accepted_nodes</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a88dbe6ff6beec0d5ff3a5fa07353d9fb</anchor>
      <arglist>(st_bfcp_conference *conference, bfcp_queue *laccepted, bfcp_list_floors *lfloors, char *chair_info)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_error_code</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ad6d95ac99ed25f36a3827793c175fa04</anchor>
      <arglist>(UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID, e_bfcp_error_codes code, const char *error_info, bfcp_unknown_m_error_details *details, BFCP_SOCKET sockfd, int i, int transport)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_show_floor_information</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ad8dd0cc34b0d6a18a44409f69ff769f0</anchor>
      <arglist>(UINT32 conferenceID, UINT16 TransactionID, UINT16 userID, st_bfcp_conference *conference, UINT16 floorID, BFCP_SOCKET sockid, fd_set allset, int *client, pnode newnode, UINT16 status)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_ChairAction_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>ad003357af408687d9160f44862e009d0</anchor>
      <arglist>(st_bfcp_server *server, UINT32 conferenceID, bfcp_floor *list_floors, UINT16 userID, UINT16 floorRequestID, int RequestStatus, char *chair_info, UINT16 queue_position, UINT16 TransactionID, BFCP_SOCKET sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>bfcp_floorrequestquery_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a0cb59cd794f37bc0359fc3a925e0a0e8</anchor>
      <arglist>(st_bfcp_server *server, UINT32 conferenceID, UINT16 TransactionID, UINT16 floorRequestID, UINT16 userID, BFCP_SOCKET sockfd, int y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>bfcp_received_msg</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a436038e9f1e6ec06e12b17a1889ef6b6</anchor>
      <arglist>(bfcp_received_message *recv_msg, BFCP_SOCKET sockfd)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ServerEvent *</type>
      <name>m_ServerEvent</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aec6fc7bbbcf6920d6e64e181bb82eab0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bfcp_mutex_t</type>
      <name>count_mutex</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>afa5ba64bead03bd33603053cf28b2911</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>st_bfcp_server *</type>
      <name>m_struct_server</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a9acf0c009193b89fad93dcf38e894dc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_bfcp_transport</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a45f0b55065d4542f44b494cc7e2ec0a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT32</type>
      <name>m_confID</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a9ceb5c984f8a7b29c05768ab9faa4ff0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_FirstUserID</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a0402512485e3d3045b8d75421b2ead4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_floorID</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>a7727dcca2fb33bf93f22275f8abced08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_streamID</name>
      <anchorfile>d3/dd0/classBFCP__Server.html</anchorfile>
      <anchor>aa06a37afc42f558a9fe73d046760f30b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCP_Server::ServerEvent</name>
    <filename>d8/ddf/classBFCP__Server_1_1ServerEvent.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>OnBfcpServerEvent</name>
      <anchorfile>d8/ddf/classBFCP__Server_1_1ServerEvent.html</anchorfile>
      <anchor>a198394b3fcf09398c5f5092f0f66eced</anchor>
      <arglist>(e_BFCP_ACT p_evt, st_BFCP_fsm_event *p_FsmEvent)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ServerEvent</name>
      <anchorfile>d8/ddf/classBFCP__Server_1_1ServerEvent.html</anchorfile>
      <anchor>a947da3ae20c406b47d8a59a0db8e5f2c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_supported_list</name>
    <filename>dc/d64/structbfcp__supported__list.html</filename>
    <member kind="variable">
      <type>UINT8</type>
      <name>element</name>
      <anchorfile>dc/d64/structbfcp__supported__list.html</anchorfile>
      <anchor>af2c71db3519d0ee6561ff573a6d6ce8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_supported_list *</type>
      <name>next</name>
      <anchorfile>dc/d64/structbfcp__supported__list.html</anchorfile>
      <anchor>ac918c3fea92e0606f85195b6987767ad</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_thread</name>
    <filename>d0/dc2/structbfcp__thread.html</filename>
    <member kind="variable">
      <type>BFCP_Server *</type>
      <name>bfcpServer</name>
      <anchorfile>d0/dc2/structbfcp__thread.html</anchorfile>
      <anchor>a3c6b8be8d43b9d78e094b3e69160d75c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>st_bfcp_conference *</type>
      <name>conf</name>
      <anchorfile>d0/dc2/structbfcp__thread.html</anchorfile>
      <anchor>aeb14e93f9dc89be842e2488e8c378b6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT32</type>
      <name>chair_wait_request</name>
      <anchorfile>d0/dc2/structbfcp__thread.html</anchorfile>
      <anchor>a958819f63fa6667075eb86f4a330c391</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>floorRequestID</name>
      <anchorfile>d0/dc2/structbfcp__thread.html</anchorfile>
      <anchor>a3e7319ec68a1db777b3a4fa068c8b058</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_unknown_m_error_details</name>
    <filename>d1/dc2/structbfcp__unknown__m__error__details.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>unknown_type</name>
      <anchorfile>d1/dc2/structbfcp__unknown__m__error__details.html</anchorfile>
      <anchor>a32c6f1da752bd935b20dc6d25c810d1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>reserved</name>
      <anchorfile>d1/dc2/structbfcp__unknown__m__error__details.html</anchorfile>
      <anchor>a2b17ef16b90dc60fe110791d4315b09a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_unknown_m_error_details *</type>
      <name>next</name>
      <anchorfile>d1/dc2/structbfcp__unknown__m__error__details.html</anchorfile>
      <anchor>a16f29af452b9cb2ba9df5cc1ec62ae87</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_user</name>
    <filename>d6/d2a/structbfcp__user.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>userID</name>
      <anchorfile>d6/d2a/structbfcp__user.html</anchorfile>
      <anchor>ad1d336c801bb4b15f20734c67c5175dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>user_URI</name>
      <anchorfile>d6/d2a/structbfcp__user.html</anchorfile>
      <anchor>a7bb97b57b5e485bb3881f8758a56c261</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>user_display_name</name>
      <anchorfile>d6/d2a/structbfcp__user.html</anchorfile>
      <anchor>aa573cc4e151a3eeeefb3418a5fd124f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>numberfloorrequest</name>
      <anchorfile>d6/d2a/structbfcp__user.html</anchorfile>
      <anchor>a2e03082bc936138704d12ebf2bc6ddf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BFCP_SOCKET</type>
      <name>sockFd</name>
      <anchorfile>d6/d2a/structbfcp__user.html</anchorfile>
      <anchor>ad73f767d2e804b4ae5b0ff1b24f5828e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct bfcp_user *</type>
      <name>next</name>
      <anchorfile>d6/d2a/structbfcp__user.html</anchorfile>
      <anchor>a13969b59507957f42d62365108b2f5b4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bfcp_user_information</name>
    <filename>db/d6c/structbfcp__user__information.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>ID</name>
      <anchorfile>db/d6c/structbfcp__user__information.html</anchorfile>
      <anchor>a9a1e87c30ebb352c3d7abfad30939a9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>display</name>
      <anchorfile>db/d6c/structbfcp__user__information.html</anchorfile>
      <anchor>af9e7e4d3e9c71439e5caae3547143e20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>uri</name>
      <anchorfile>db/d6c/structbfcp__user__information.html</anchorfile>
      <anchor>a49b05e7132385fb123c46cf97ec8ef89</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCP_UserList</name>
    <filename>d6/dbb/classBFCP__UserList.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>BFCP_UserList_error_code</name>
      <anchorfile>d6/dbb/classBFCP__UserList.html</anchorfile>
      <anchor>ad05377f9d473f6720940d52aebfd971d</anchor>
      <arglist>(UINT32 conferenceID, UINT16 userID, UINT16 TransactionID, e_bfcp_error_codes code, char *error_info, bfcp_unknown_m_error_details *details, int sockfd, int i, int transport)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCPApi</name>
    <filename>db/d2c/classBFCPApi.html</filename>
    <base>BFCP_Participant::ParticipantEvent</base>
    <base>BFCP_Server::ServerEvent</base>
    <class kind="class">BFCPApi::BFCPApiEvent</class>
    <member kind="typedef">
      <type>BFCP_fsm::st_BFCP_fsm_event</type>
      <name>s_bfcpApi_event</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a4bedc82e31b3f162787192257b4f12f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BFCPApi</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a01fda24f8d8e7ee45eaa34326e8e86d1</anchor>
      <arglist>(BFCPApiEvent *p_listener)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~BFCPApi</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a2976406c9da3a46fbb4c914d5db9d8c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>BFCPApiOpenTcpConnection</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a59f5f269a1c64a9a141616ef97b32dee</anchor>
      <arglist>(const char *local_address, int local_port, const char *remote_address, int remote_port)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>BFCPApiCloseTcpConnection</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ac5c74fe56204cff63b9125e364498756</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetWindowHandle</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a9d83b4d96493bcde145e17e74f4f951c</anchor>
      <arglist>(HWND hWndApplicationSelected)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCodecControllerAPI</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>aac730313cccbf982f691e9f4eb19bebb</anchor>
      <arglist>(CodecControllerAPI *pCodecControler)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCallControllerAPI</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>afefe0f6372201664f6ab44bbffe9ad4c</anchor>
      <arglist>(CallControllerAPI *pCallControler, const void *pCallStackGroup)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setConfHandle</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a597726db736243a774ef9b75bfd275a9</anchor>
      <arglist>(const void *pConfHandle)</arglist>
    </member>
    <member kind="function">
      <type>const void *</type>
      <name>GetWindowGrabber</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a18a79ebf3b5e5292bb885f7bb53b97f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetConfID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>aca1de47fa66b44d8b5417626be18f6dd</anchor>
      <arglist>(UINT32 p_confID)</arglist>
    </member>
    <member kind="function">
      <type>UINT32</type>
      <name>GetConfID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a99168ee3e000e2b78ea699e2ad44dcb5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUserID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a06b53b1c8b0ef3d13307b2d92ff3b678</anchor>
      <arglist>(UINT16 p_userID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetUserID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a1ba73271a2d45e07ffe56173ea1845af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFloorID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a802aa0c3f9357378c08866ec17b9f14c</anchor>
      <arglist>(UINT16 p_floorID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetFloorID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a4b383f8882aa84841948f6bcef8e756d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStreamID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ae795d2c9f1eb1222155f3a4e05288d1b</anchor>
      <arglist>(UINT16 p_streamID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetStreamID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a3629e08f32d3cb220b1f7349528d434c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetIsPassive</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ae92a418a8c7b9b4d273a0a311d66db99</anchor>
      <arglist>(bool p_IsServer)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetIsPassive</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a2c0e618366b3dbe4bf49eee6d5d97b86</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFloorctrlMode</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>aa9de5a79942e343fa29db8924bd7b4d4</anchor>
      <arglist>(e_floorctrlMode pfloorctrlMode)</arglist>
    </member>
    <member kind="function">
      <type>e_floorctrlMode</type>
      <name>GetFloorctrlMode</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a17bd92fce6d87134efe018b9e4ea10c9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetConfID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>aca1de47fa66b44d8b5417626be18f6dd</anchor>
      <arglist>(UINT32 p_confID)</arglist>
    </member>
    <member kind="function">
      <type>UINT32</type>
      <name>GetConfID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a99168ee3e000e2b78ea699e2ad44dcb5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUserID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a06b53b1c8b0ef3d13307b2d92ff3b678</anchor>
      <arglist>(UINT16 p_userID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetUserID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a1ba73271a2d45e07ffe56173ea1845af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFloorID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a802aa0c3f9357378c08866ec17b9f14c</anchor>
      <arglist>(UINT16 p_floorID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetFloorID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a4b383f8882aa84841948f6bcef8e756d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStreamID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ae795d2c9f1eb1222155f3a4e05288d1b</anchor>
      <arglist>(UINT16 p_streamID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetStreamID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a3629e08f32d3cb220b1f7349528d434c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetIsPassive</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ae92a418a8c7b9b4d273a0a311d66db99</anchor>
      <arglist>(bool p_IsServer)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetIsPassive</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ac6b81319cbcedc5e3a4e2c911c9c2e05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddUserIDinConf</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a065a3cdc20188f027f0478463effe424</anchor>
      <arglist>(UINT16 p_userID)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RemoveUserIDinConf</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>af7f84019a4bbad1f120d60e0775320f3</anchor>
      <arglist>(UINT16 p_userID)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnConnectedCall</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a1ea85dddd0da4f93edecc49f8281ea1e</anchor>
      <arglist>(const void *confHandle, const void *callHandle, RemotePartyInformations &amp;informations)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnReadyToOpenChannels</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a6874ffc79803db35bada52862ed92a08</anchor>
      <arglist>(const void *handle)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnEndOfCall</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a1e97e13a358fe54895bb2631475aefba</anchor>
      <arglist>(const void *handle, const unsigned int reason, const TCHAR *szExtendedReason)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnChannelCreated</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a656c8658d9e41465d37f99faeeec7dfc</anchor>
      <arglist>(const void *handle, const unsigned int channelId, Direction dir, FtCodecType type, Codec *codec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnChannelDestroyed</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a08f3efb4d777e57b2db5dd6623f9a9c7</anchor>
      <arglist>(const void *handle, const unsigned int channelId, Direction dir, FtCodecType type, Codec *codec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const void *</type>
      <name>OnWindowGrabberCreated</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a8683c215952feb35dc51659c209e47bc</anchor>
      <arglist>(const void *callHandle, const unsigned int channelId, const void *windowGrabber, VideoFormatStruct *format, Codec *codec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnModuleRemoved</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a819ca4d28a2e6cc2831538b3b727afb8</anchor>
      <arglist>(const void *confHandle, const void *module)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const unsigned int</type>
      <name>OnCanUseCodecForAnOutgoingChannel</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>adbcd4e5b3cdc012b3e40e21893084ef0</anchor>
      <arglist>(const void *callHandle, Codec *codec)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnError</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a7a8b90f64ce9156c1eb7714551ca2916</anchor>
      <arglist>(const void *handle, unsigned int errorCode)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>OnBfcpParticipantEvent</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a2b88d710bde61094246d397cc10f1bb5</anchor>
      <arglist>(BFCP_fsm::e_BFCP_ACT p_evt, BFCP_fsm::st_BFCP_fsm_event *p_FsmEvent)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>OnBfcpServerEvent</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a7a4ca941732bc369d79469d8b401bf4b</anchor>
      <arglist>(BFCP_fsm::e_BFCP_ACT p_evt, BFCP_fsm::st_BFCP_fsm_event *p_FsmEvent)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>connected</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a58d401089e9cb4544ecf13bb1a607448</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>disconnected</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a606e5c0cc5d953d7ac3f2da044757168</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>floorRequestStatusAccepted</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a326ad39aacd9e7e5a74775632c12ef85</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>floorRequestStatusGranted</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a15352cd3c3e3100601c35f5b481ea142</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>floorRequestStatusAborted</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ac813330b06a25286682b31ab5210bb29</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>floorStatusAccepted</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ae7fa2c9ddada2b68bae9d4359587ce27</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>floorStatusGranted</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a15c36a7aa8761bf1314cba912e2f380d</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>floorStatusAborted</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>aebb768fd6e75be244a4cb3a9f738fa38</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>floorReleaseStatusAborted</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a094c481aade04b5997cebb034b117e82</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetWindowHandle2Grabber</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ac43f69232d0f2d98ba11018d00374a7b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>floorRequest</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a7dfbc46d2e242880cc158ec4bc5f2b1c</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>floorRelease</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a6337695529eaf9db4db9929e5df8d40b</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>updateHwnd</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a5e17361c3a909843b86f7cd70ec7c6d1</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>BFCPApiOpenServerTcpConnection</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a80fb3a71f01a42f39e4e9b0bd7b23ffc</anchor>
      <arglist>(const char *local_address, int local_port, const char *remote_address, int remote_port, bool isPassive)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>BFCPApiOpenParticipantTcpConnection</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a52b1504fe0318f9bf162506667671dd5</anchor>
      <arglist>(const char *local_address, int local_port, const char *remote_address, int remote_port, bool isPassive)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BFCP_Participant *</type>
      <name>m_BFCP_Participant</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a32810adbfa002cd426e5315a8b617b9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BFCP_Server *</type>
      <name>m_BFCP_Server</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a86b9b6ab57401fd519f21714fc14637f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const void *</type>
      <name>m_windowGrabber</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a3d599adbfd43b2bcd8866fd8ebe7c5c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const void *</type>
      <name>m_confHandle</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a7a637de6cafdde519bc83aaa30737f14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>CodecControllerAPI *</type>
      <name>m_codecControler</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ad38b2cce46e7bac0f703020987e5b429</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>CallControllerAPI *</type>
      <name>m_callControler</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a7c4701b7e5ca0262e144ed4197449f28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>void *</type>
      <name>m_callStackGroup</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a379988e119758df205fb0886b0f1a605</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>e_floorctrlMode</type>
      <name>m_e_floorctrlMode</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a6da4307e951fc395e64896461046fd3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>HWND</type>
      <name>m_hWndApplicationSelected</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>af721e6e46d0f32cce3a4a67ea63a516d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT32</type>
      <name>m_confID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ad25285e948656c35840404226988a880</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_userID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a8e6b450a272f7d4bdc8acb7a992477ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_floorID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a4b12191c6223e5600bf9d61a8676cd28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_streamID</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>ab1d6d7fb5e4bb6d2097a9d2594d39527</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_IsPassive</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a6957c90bfe26d5edcd9443db29541758</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BFCPApiEvent *</type>
      <name>m_listener</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a589d649c8c40f9bf610e82a88acc1c82</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bfcp_mutex_t</type>
      <name>m_mutexServer</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>a632024736462a56f1501d20d20b9e34a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bfcp_mutex_t</type>
      <name>m_mutexParticipant</name>
      <anchorfile>db/d2c/classBFCPApi.html</anchorfile>
      <anchor>acb3d5e4d3ec63d77dd7795fe5f8af386</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCPApi::BFCPApiEvent</name>
    <filename>dd/d74/classBFCPApi_1_1BFCPApiEvent.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>OnBfcpApiConnected</name>
      <anchorfile>dd/d74/classBFCPApi_1_1BFCPApiEvent.html</anchorfile>
      <anchor>a1d98523d69aa36b530adb6c5e3564c37</anchor>
      <arglist>(bool p_connected)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>OnBfcpApiEvent</name>
      <anchorfile>dd/d74/classBFCPApi_1_1BFCPApiEvent.html</anchorfile>
      <anchor>a9a4d45bf1f7f61e91c7abe84650f7ea0</anchor>
      <arglist>(void *p_ApiEvent)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCPConnection</name>
    <filename>d1/d42/classBFCPConnection.html</filename>
    <class kind="struct">BFCPConnection::Client2ServerInfo</class>
    <member kind="function" virtualness="pure">
      <type>virtual bfcp_message *</type>
      <name>readAndProcessBFCPmessage</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a1f1076e1d8eac7617bf4c18a53d78517</anchor>
      <arglist>(BFCP_SOCKET socket)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>OnBFCPConnected</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>aad7c3c82356539e4296da0f8ade7e90d</anchor>
      <arglist>(BFCP_SOCKET socket, char *RemoteIp, int remotePort)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>OnBFCPDisconnected</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a04659673122dd2d12d52beafa17f7332</anchor>
      <arglist>(BFCP_SOCKET socket, char *RemoteIp, int remotePort)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Log</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>aef7dc5f75a3fc7ed17465bea38255459</anchor>
      <arglist>(const char *pcFile, int iLine, int iErrorLevel, const char *pcFormat,...)=0</arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>struct BFCPConnection::Client2ServerInfo</type>
      <name>Client2ServerInfo</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>af1e27cc2886fea39ebb2c915ca9462ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>transmitLoop</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a9973abf0a905647eed79b07d94084af6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>unsigned long</type>
      <name>availableBytes</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a060520405c1c15d318ca552a981bfd94</anchor>
      <arglist>(BFCP_SOCKET p_sock)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bfcp_mutex_t</type>
      <name>m_mutConnect</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a708faf8ed243aa3a9f0fb667c2650348</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bfcp_mutex_t</type>
      <name>m_mutDisconnect</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a85d519681f88bb47223d11ebf5632966</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bfcp_mutex_t</type>
      <name>m_SessionMutex</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a3c8bd9ae72330138fe94c4d616c9237a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::map&lt; BFCP_SOCKET, Client2ServerInfo &gt;</type>
      <name>m_ClientSocket</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>ab051d3a7c3a308bf26964cdb71a44b3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BFCP_SOCKET</type>
      <name>m_Socket</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a0ad7ed37d2568a7b9499ecd509853556</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BFCP_THREAD_HANDLE</type>
      <name>m_thread</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a1b61b2f336c70b0f2e2817f37558c654</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>fd_set</type>
      <name>m_wset</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a48d065dfe235af0bf33989a544214323</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bClose</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a5dd0156ea055df5d3724c51a8c1f9426</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_eRole</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a381cb018c1dc7cf1bbb393917cadd05f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>char</type>
      <name>m_localAdress</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a824d354e1ca70016294ae55be7095e15</anchor>
      <arglist>[PATH_MAX]</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_localPort</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>aab69ed13cf3ff2eda6268891141c80fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>char</type>
      <name>m_remoteAdress</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a8286377510aa3ed7d8307be18b25ae08</anchor>
      <arglist>[PATH_MAX]</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_remotePort</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>adab8d0adf07c31ede1690d8bc3d58dca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bConnected</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>acec5fb4f159c2d902a9bfedff8139270</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_isStarted</name>
      <anchorfile>d1/d42/classBFCPConnection.html</anchorfile>
      <anchor>a93604caed8f8108134ac02870f6de173</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>BFCPConnection::Client2ServerInfo</name>
    <filename>d7/d12/structBFCPConnection_1_1Client2ServerInfo.html</filename>
    <member kind="variable">
      <type>char</type>
      <name>m_remoteAdress</name>
      <anchorfile>d7/d12/structBFCPConnection_1_1Client2ServerInfo.html</anchorfile>
      <anchor>aa8d3a8c50729ab858b6cb54d327f6161</anchor>
      <arglist>[PATH_MAX]</arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>m_remotePort</name>
      <anchorfile>d7/d12/structBFCPConnection_1_1Client2ServerInfo.html</anchorfile>
      <anchor>a9c28c0d700eda56aee51cd1137572360</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCPConnectionRole</name>
    <filename>db/d81/classBFCPConnectionRole.html</filename>
    <member kind="function">
      <type></type>
      <name>BFCPConnectionRole</name>
      <anchorfile>db/d81/classBFCPConnectionRole.html</anchorfile>
      <anchor>a444ddce25a7f1e3b94a138d37f79d24d</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BFCPConnectionRole</name>
      <anchorfile>db/d81/classBFCPConnectionRole.html</anchorfile>
      <anchor>a34cd83d8bd89415ed48d596b113f6ae3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>ACTIVE</name>
      <anchorfile>db/d81/classBFCPConnectionRole.html</anchorfile>
      <anchor>aa59a20b17ff3e180c99c0394b47604fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>PASSIVE</name>
      <anchorfile>db/d81/classBFCPConnectionRole.html</anchorfile>
      <anchor>a5453068a9274bf6dccbf663e7ab148a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCPException</name>
    <filename>de/dea/classBFCPException.html</filename>
    <member kind="variable" protection="private">
      <type>std::string</type>
      <name>msg</name>
      <anchorfile>de/dea/classBFCPException.html</anchorfile>
      <anchor>abb4bd166ebbb16f2ff1f73be36252dbb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCPinputstream</name>
    <filename>d7/db1/classBFCPinputstream.html</filename>
    <member kind="function">
      <type>ssize_t</type>
      <name>read</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>af6898d00e0c82ab60b003f6df090e96a</anchor>
      <arglist>(char &amp;c)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ungetc</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>af04ed5d2847b80308f5b20f8d7ec43a4</anchor>
      <arglist>(char c)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>read</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a6f6ddcdaa32ccf765563ae0e6738275c</anchor>
      <arglist>(size_t &amp;count)</arglist>
    </member>
    <member kind="function">
      <type>ssize_t</type>
      <name>read</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>aba0352dbf66f5bbc5a84b2f846e67420</anchor>
      <arglist>(char *buffer, size_t count)</arglist>
    </member>
    <member kind="function">
      <type>off_t</type>
      <name>available</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a285ae81f6a7e72ec6a11453e71b44bce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>skip</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a47c04d8a6f181f05eff80f2997f3157f</anchor>
      <arglist>(size_t len)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>BFCPinputstream</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>ac89e81fee5f16a1ca78c32f2a50fe598</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~BFCPinputstream</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a8f749814e0c7a2339cf7e3f51f97afe2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setBuffer</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>ade37a9f74a4930737faa8a41a96ba212</anchor>
      <arglist>(const char *start, off_t size)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>off_t</type>
      <name>queryBuffer</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>aca27fd5d7505cedd4a128f812fd29cef</anchor>
      <arglist>(char **start)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static const off_t</type>
      <name>DefaultBufferSize</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a8df77e0bc225ea0301de21efbd7bca0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private" virtualness="pure">
      <type>virtual ssize_t</type>
      <name>readBytes</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>aa77d49336eb4a84f428fc49dfc19c0b0</anchor>
      <arglist>(char *buffer, size_t count)=0</arglist>
    </member>
    <member kind="function" protection="private" virtualness="pure">
      <type>virtual unsigned long</type>
      <name>availableBytes</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a4eded4e15b60e0a69efd6d028db65f54</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="private">
      <type>off_t</type>
      <name>bufferize</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a4fd79ab4d7d13f992f84de2dc8a6916c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const char *</type>
      <name>m_start</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>afa02872be388a552789770c119774306</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>char *</type>
      <name>m_pos</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a0c85b2d63ece4c13eb7543f03cde58c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>off_t</type>
      <name>m_left</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a955a8698575faf9b53e6c8a4be38fddc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>off_t</type>
      <name>m_size</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a95758ed04d57630be61985cb6cd12b55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_allocated</name>
      <anchorfile>d7/db1/classBFCPinputstream.html</anchorfile>
      <anchor>a1052c7c7bc0b6a155adf5d2e25be65d8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>BFCPOutputStream</name>
    <filename>d5/d76/classBFCPOutputStream.html</filename>
    <member kind="function">
      <type></type>
      <name>BFCPOutputStream</name>
      <anchorfile>d5/d76/classBFCPOutputStream.html</anchorfile>
      <anchor>ae006d14fbb0a3a1c2c43fb6f7088c9bf</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BFCPOutputStream</name>
      <anchorfile>d5/d76/classBFCPOutputStream.html</anchorfile>
      <anchor>a5b4ea4c06588a15cfd2d2306f0452a50</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>write</name>
      <anchorfile>d5/d76/classBFCPOutputStream.html</anchorfile>
      <anchor>a8494960c26bd7dc460e9a11f32b86f8c</anchor>
      <arglist>(char b)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>write</name>
      <anchorfile>d5/d76/classBFCPOutputStream.html</anchorfile>
      <anchor>a1a71922e04550f9bad713f082d04fabb</anchor>
      <arglist>(const char *data, unsigned len)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>flush</name>
      <anchorfile>d5/d76/classBFCPOutputStream.html</anchorfile>
      <anchor>aae1fd37b5551b17af8b7b37e8e318e87</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>close</name>
      <anchorfile>d5/d76/classBFCPOutputStream.html</anchorfile>
      <anchor>a17026f293a7088789e4be2a6dfa7121d</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ByteArrayBFCPinputstream</name>
    <filename>df/d0f/classByteArrayBFCPinputstream.html</filename>
    <base>BFCPinputstream</base>
    <member kind="function">
      <type></type>
      <name>ByteArrayBFCPinputstream</name>
      <anchorfile>df/d0f/classByteArrayBFCPinputstream.html</anchorfile>
      <anchor>aca8194cda2b20f858f7e02670da1447b</anchor>
      <arglist>(const char *bytes, off_t size)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ByteArrayBFCPinputstream</name>
      <anchorfile>df/d0f/classByteArrayBFCPinputstream.html</anchorfile>
      <anchor>a95e1fed808412bc9f4890399ccfc5771</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>ByteArrayBFCPinputstream</name>
      <anchorfile>df/d0f/classByteArrayBFCPinputstream.html</anchorfile>
      <anchor>a547eaea47f442c5f34c5d7618a6df94f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual ssize_t</type>
      <name>readBytes</name>
      <anchorfile>df/d0f/classByteArrayBFCPinputstream.html</anchorfile>
      <anchor>addc15fdafad33073a8600933aa694f99</anchor>
      <arglist>(char *buffer, size_t count)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual unsigned long</type>
      <name>availableBytes</name>
      <anchorfile>df/d0f/classByteArrayBFCPinputstream.html</anchorfile>
      <anchor>a9c3bd9beb0b5abdfe1b158672787cc70</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FileBFCPinputstream</name>
    <filename>dc/d16/classFileBFCPinputstream.html</filename>
    <base>BFCPinputstream</base>
    <member kind="function">
      <type></type>
      <name>FileBFCPinputstream</name>
      <anchorfile>dc/d16/classFileBFCPinputstream.html</anchorfile>
      <anchor>a0bb301a1a39cae5121fcdaf8d27bcdc6</anchor>
      <arglist>(std::string filename)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FileBFCPinputstream</name>
      <anchorfile>dc/d16/classFileBFCPinputstream.html</anchorfile>
      <anchor>aee5aab157bd4333d6d4fa99add98e85c</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned long</type>
      <name>size</name>
      <anchorfile>dc/d16/classFileBFCPinputstream.html</anchorfile>
      <anchor>a0857409a6f9aec38dda94a358ca53319</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>FileBFCPinputstream</name>
      <anchorfile>dc/d16/classFileBFCPinputstream.html</anchorfile>
      <anchor>a2655c795d36e6fb1f21e4efb3af08846</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual ssize_t</type>
      <name>readBytes</name>
      <anchorfile>dc/d16/classFileBFCPinputstream.html</anchorfile>
      <anchor>aa9a0313a78149978bfb3e02c6d827e5a</anchor>
      <arglist>(char *buffer, size_t count)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual unsigned long</type>
      <name>availableBytes</name>
      <anchorfile>dc/d16/classFileBFCPinputstream.html</anchorfile>
      <anchor>aa8307e71f391e657bbf91c816834d28e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>FILE *</type>
      <name>m_hfile</name>
      <anchorfile>dc/d16/classFileBFCPinputstream.html</anchorfile>
      <anchor>a8f9bb33a540dcd99fa9cba44f93239f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>long</type>
      <name>m_lSize</name>
      <anchorfile>dc/d16/classFileBFCPinputstream.html</anchorfile>
      <anchor>af9956248d0226b34dc00ad52d394c376</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FileBFCPOutputStream</name>
    <filename>d9/d0d/classFileBFCPOutputStream.html</filename>
    <base>BFCPOutputStream</base>
    <member kind="function">
      <type></type>
      <name>FileBFCPOutputStream</name>
      <anchorfile>d9/d0d/classFileBFCPOutputStream.html</anchorfile>
      <anchor>a8cd46b69f42f8c10bbb1f9e401313fb1</anchor>
      <arglist>(std::string filename)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FileBFCPOutputStream</name>
      <anchorfile>d9/d0d/classFileBFCPOutputStream.html</anchorfile>
      <anchor>ae3c4acce6b3789942d7c37314df4d804</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>write</name>
      <anchorfile>d9/d0d/classFileBFCPOutputStream.html</anchorfile>
      <anchor>a462f9d544f5f0a7c57add4f90aff2624</anchor>
      <arglist>(char b)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>write</name>
      <anchorfile>d9/d0d/classFileBFCPOutputStream.html</anchorfile>
      <anchor>a539d3189107b8e4b42edf2d208a056b6</anchor>
      <arglist>(const char *data, unsigned len)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>flush</name>
      <anchorfile>d9/d0d/classFileBFCPOutputStream.html</anchorfile>
      <anchor>acc01558b9fe4c4a60bc3d67735fe15ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>close</name>
      <anchorfile>d9/d0d/classFileBFCPOutputStream.html</anchorfile>
      <anchor>afd92d036ff513f09039fa54d6ae7045f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>FILE *</type>
      <name>m_hfile</name>
      <anchorfile>d9/d0d/classFileBFCPOutputStream.html</anchorfile>
      <anchor>a0f8a3f8d24d4668d2dc94d26979b354e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FileNotFoundException</name>
    <filename>da/dda/classFileNotFoundException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>FileNotFoundException</name>
      <anchorfile>da/dda/classFileNotFoundException.html</anchorfile>
      <anchor>ade06f0cd48d712b2377a37cd8aff9cc0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FileNotFoundException</name>
      <anchorfile>da/dda/classFileNotFoundException.html</anchorfile>
      <anchor>a665392a7640372bce5afd54abc34a09a</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>floor_query</name>
    <filename>d7/def/structfloor__query.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>userID</name>
      <anchorfile>d7/def/structfloor__query.html</anchorfile>
      <anchor>af910417a769344c16728a19961266169</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>fd</name>
      <anchorfile>d7/def/structfloor__query.html</anchorfile>
      <anchor>a10e5c2b38f7d73d82dbd1746d298f5a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct floor_query *</type>
      <name>next</name>
      <anchorfile>d7/def/structfloor__query.html</anchorfile>
      <anchor>a7f7c5dd02e9f8caea3081dcdb6817b4f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>floor_request_query</name>
    <filename>dc/dcf/structfloor__request__query.html</filename>
    <member kind="variable">
      <type>UINT16</type>
      <name>userID</name>
      <anchorfile>dc/dcf/structfloor__request__query.html</anchorfile>
      <anchor>a310603a48b953bdd73bef2ea8b395150</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>fd</name>
      <anchorfile>dc/dcf/structfloor__request__query.html</anchorfile>
      <anchor>a722cb7da80cc5466a629a46968c713c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct floor_request_query *</type>
      <name>next</name>
      <anchorfile>dc/dcf/structfloor__request__query.html</anchorfile>
      <anchor>a8433ccce603641ad6c4471b8715926ce</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IllegalArgumentException</name>
    <filename>d8/d68/classIllegalArgumentException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>IllegalArgumentException</name>
      <anchorfile>d8/d68/classIllegalArgumentException.html</anchorfile>
      <anchor>a5d04705d2de3440384c253e75bb3e848</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IllegalArgumentException</name>
      <anchorfile>d8/d68/classIllegalArgumentException.html</anchorfile>
      <anchor>a9e3c5035e787b73c6399414837fe232b</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>InternalProgramError</name>
    <filename>d8/d7a/classInternalProgramError.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>InternalProgramError</name>
      <anchorfile>d8/d7a/classInternalProgramError.html</anchorfile>
      <anchor>a0cd3d4473eefe2147d4aa116aca75f8c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InternalProgramError</name>
      <anchorfile>d8/d7a/classInternalProgramError.html</anchorfile>
      <anchor>a1726a2243a87df4cc2c1eccf6532ba7d</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>InterruptedException</name>
    <filename>d2/d40/classInterruptedException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>InterruptedException</name>
      <anchorfile>d2/d40/classInterruptedException.html</anchorfile>
      <anchor>aa985c5a013b0a969ece81e79925cd4a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InterruptedException</name>
      <anchorfile>d2/d40/classInterruptedException.html</anchorfile>
      <anchor>a9a8065116bcfaf3856cddf228dd665f0</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>InvalidFieldException</name>
    <filename>da/d45/classInvalidFieldException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>InvalidFieldException</name>
      <anchorfile>da/d45/classInvalidFieldException.html</anchorfile>
      <anchor>ab710565f122637553cc5d90735130ec2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InvalidFieldException</name>
      <anchorfile>da/d45/classInvalidFieldException.html</anchorfile>
      <anchor>af39e343edd1b8b18e7d10834f7184484</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>InvalidParameterException</name>
    <filename>d1/db2/classInvalidParameterException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>InvalidParameterException</name>
      <anchorfile>d1/db2/classInvalidParameterException.html</anchorfile>
      <anchor>acc94b2f3a9f1ea85831dacfcc546bb20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InvalidParameterException</name>
      <anchorfile>d1/db2/classInvalidParameterException.html</anchorfile>
      <anchor>a38a6221e3f8bc3eae6e2bd3dfaf8797b</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IOException</name>
    <filename>d3/d1e/classIOException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>IOException</name>
      <anchorfile>d3/d1e/classIOException.html</anchorfile>
      <anchor>ad1e8e7e09716ddc197a23611250fa180</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IOException</name>
      <anchorfile>d3/d1e/classIOException.html</anchorfile>
      <anchor>a6240a4ec8e8d23d39f6ad048089748cd</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MessageMissformedException</name>
    <filename>d8/d99/classMessageMissformedException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>MessageMissformedException</name>
      <anchorfile>d8/d99/classMessageMissformedException.html</anchorfile>
      <anchor>ab9d33ac5511fe8c56be4a88818157625</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MessageMissformedException</name>
      <anchorfile>d8/d99/classMessageMissformedException.html</anchorfile>
      <anchor>a39a819dfa4ccac13d3bdaa7317865203</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>OpenFileErrorException</name>
    <filename>d8/db7/classOpenFileErrorException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>OpenFileErrorException</name>
      <anchorfile>d8/db7/classOpenFileErrorException.html</anchorfile>
      <anchor>a8686599de70f02086d5aad31f0e78943</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OpenFileErrorException</name>
      <anchorfile>d8/db7/classOpenFileErrorException.html</anchorfile>
      <anchor>aa9cf319353ca215e2f54ee1eb9238c19</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ParseException</name>
    <filename>d3/d3c/classParseException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>ParseException</name>
      <anchorfile>d3/d3c/classParseException.html</anchorfile>
      <anchor>a6a162a3a6aeed5e133adfacf0dfd4cad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ParseException</name>
      <anchorfile>d3/d3c/classParseException.html</anchorfile>
      <anchor>a0e2db737183a1801d528102617ddc3c4</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PayloadOverflowException</name>
    <filename>d0/d27/classPayloadOverflowException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>PayloadOverflowException</name>
      <anchorfile>d0/d27/classPayloadOverflowException.html</anchorfile>
      <anchor>a2c6a19a1addee2d62993a3969aff9bd3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PayloadOverflowException</name>
      <anchorfile>d0/d27/classPayloadOverflowException.html</anchorfile>
      <anchor>a3b552e1984a35ba7f9effd78ddb1d315</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RequestMethodException</name>
    <filename>dd/df7/classRequestMethodException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>RequestMethodException</name>
      <anchorfile>dd/df7/classRequestMethodException.html</anchorfile>
      <anchor>a3636e709b05bb0b9164623a56575e8ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RequestMethodException</name>
      <anchorfile>dd/df7/classRequestMethodException.html</anchorfile>
      <anchor>a92bdb7ecb2e63ec0ff5ddd0d79a813b0</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>s_bfcp_msg_event</name>
    <filename>df/d41/structs__bfcp__msg__event.html</filename>
    <member kind="variable">
      <type>e_bfcp_primitives</type>
      <name>Event</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a72abf437869e7e6d855d9d88e1a18c0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_status</type>
      <name>Status</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a1b5200e02b71bf39c175d611a50ac10b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_status</type>
      <name>FloorStatus</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a222baedfa0a0c1f0030f2b72dda90327</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_attibutes</type>
      <name>Attibutes</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a833a6da61efdc73aa329da5f89239eb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_priority</type>
      <name>Priority</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a02ce2c30ad4a6568896c7da6b17a6588</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_error_codes</type>
      <name>Error_codes</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a8fbb9ec0683afdb550d59ebdb2ac1e06</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>e_bfcp_specific_error_codes</type>
      <name>Specific_error_codes</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a07dabfd1d014e52e92f8bd40bfc7a5c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>TransactionID</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>ab426365d6ab4794b821a04375a7383a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>userID</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a733fa7c529128f7e5e321e93d33ce355</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT32</type>
      <name>conferenceID</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a01bd599caa91dbd88c3b8cefb9fd0cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>FloorID</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a6234e31dab99e1efea05b0f36e270d3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>FloorRequestID</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>ad76101f741f816c7f48ced18254f6717</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>QueuePosition</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a0769ba0892bf3d23591bee4bb1d8e2c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>BeneficiaryID</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a929393c531410a98d75b8c92ab9563a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BFCP_SOCKET</type>
      <name>sockfd</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a945a6cd68454f57de2fb16413efb656e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>i_parm</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a913e1ea6ed67d64bdba5ff56f6145b8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>c_param</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a90af5359267f946c4d3be899db70f7c3</anchor>
      <arglist>[BFCP_STRING_SIZE]</arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>pt_param</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a74641fc7569f9ef7e2c250edb5b6ded0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT8</type>
      <name>Support_primitives</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a3c101eb5a04fa557766e7fe8cc27649d</anchor>
      <arglist>[BFCP_MAX_RG]</arglist>
    </member>
    <member kind="variable">
      <type>UINT8</type>
      <name>Support_attributes</name>
      <anchorfile>df/d41/structs__bfcp__msg__event.html</anchorfile>
      <anchor>a3a843508cf744b69ddce913c8517cb40</anchor>
      <arglist>[BFCP_MAX_RG]</arglist>
    </member>
    <docanchor file="df/d41/structs__bfcp__msg__event" title="BFCP common header Format">BFCP-COMMON-HEADER</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title=": The 3-bit version field MUST be set to 1 to indicate this">Ver</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title=": At this point, the 5 bits in the reserved field SHOULD be">Reserved</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title=": This 8-bit field identifies the main purpose of the">Primitive</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title="Length: This 16-bit field contains the length of the message">Payload</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title="ID: This 32-bit field identifies the conference the">Conference</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title="ID: This field contains a 16-bit value that allows users">Transaction</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title="ID: This field contains a 16-bit value that uniquely identifies">User</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title="attributes Format">BFCP</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title=": This 7-bit field contains the type of the attribute.  Each">Type</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title=": This 8-bit field contains the length of the attribute in">Length</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title="Contents: The contents of the different attributes are">Attribute</docanchor>
    <docanchor file="df/d41/structs__bfcp__msg__event" title="ID: This field contains a 16-bit value that uniquely">Beneficiary</docanchor>
  </compound>
  <compound kind="class">
    <name>sampleClient</name>
    <filename>dc/d28/classsampleClient.html</filename>
    <base>BFCP_Participant::ParticipantEvent</base>
    <member kind="function">
      <type></type>
      <name>sampleClient</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>acf5b0732ec0491bca00cba6a7aaddddd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~sampleClient</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a2bdcc887c00163cd1436c6d819d9f1f6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetConfID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a324149bdc63a0e60458ec850f7e6c4aa</anchor>
      <arglist>(UINT32 p_confID)</arglist>
    </member>
    <member kind="function">
      <type>UINT32</type>
      <name>GetConfID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a9adbf747dace8265d28613f47aea771e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUserID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a7822ee8af93d486e27c4d2b4113c6896</anchor>
      <arglist>(UINT16 p_userID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetUserID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>adcb82d4eb53fed4d0c1aa750c78683ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFloorID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a26a8ffe04645d742ddb13e573cf247be</anchor>
      <arglist>(UINT16 p_floorID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetFloorID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a6a1a180fa54275bab5187bd775d8f806</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStreamID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>aa81e30543090a3e9ee78d8a546719670</anchor>
      <arglist>(UINT16 p_streamID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetStreamID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a0e9594b9fbf06f6ee88dfa1bfc675c7e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetIsPassive</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a4651763419a6ec7ec068d07dfb0ae0dd</anchor>
      <arglist>(bool p_IsServer)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetIsPassive</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>ae483bddb1fa9b0769eb2816b1cfadf0f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFloorctrlMode</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a70e2458423a220e9661782590ba95ae0</anchor>
      <arglist>(e_floorctrlMode pfloorctrlMode)</arglist>
    </member>
    <member kind="function">
      <type>e_floorctrlMode</type>
      <name>GetFloorctrlMode</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a3d80fad76e7fc29735e2af0e138ccf77</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>menu</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a7988a4f417d24d4be0a4e70e3ad7faf2</anchor>
      <arglist>(char *lineptr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>OnBfcpParticipantEvent</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a237d550ee5831330971cb92240c6cb4c</anchor>
      <arglist>(BFCP_fsm::e_BFCP_ACT p_evt, BFCP_fsm::st_BFCP_fsm_event *p_FsmEvent)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Log</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>abe57c9d9eacd69ff0f0c47b44c75df85</anchor>
      <arglist>(const char *pcFile, int iLine, int iErrorLevel, const char *pcFormat,...)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>connected</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>abf908ecc5963f84b14439a6c59adb732</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>disconnected</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>af34ee15dce9d19513c7c873efc1a2dc3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>floorRequestStatusAccepted</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a56c640ede0803822c5a696925d179a10</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>floorRequestStatusGranted</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a61d57b9f201707373ecf7861fcb12519</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>floorRequestStatusAborted</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a51afe3ce1313fb637e6dce6c85448577</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>floorStatusAccepted</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a8a68c64c8b6f3d5737ca2ca10dcf956a</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>floorStatusGranted</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>ad7bd4ca4174d59a913a55c5244de19a2</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>floorStatusAborted</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>aa129f11039f87fd710e918b960b7d1a4</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>floorReleaseStatusAborted</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a11eba49310045aa31312e5a16734886d</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>floorRequest</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>ac109ddd8b45b76538da4867ead2960ec</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>floorRelease</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a4bbc2cc148134e252eece5aa537b3ff2</anchor>
      <arglist>(BFCP_fsm::st_BFCP_fsm_event *p_evt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>OpenParticipantTcpConnection</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>aef071df8948ca2f4dc3beed2fc85a5d3</anchor>
      <arglist>(const char *local_address, int local_port, const char *remote_address, int remote_port, bool isPassive)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BFCP_Participant *</type>
      <name>m_BFCP_Participant</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a129e5c75c6886b170a5ca3f5995e2c43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>e_floorctrlMode</type>
      <name>m_e_floorctrlMode</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a828eb8f4570a9e1d713552437a2704e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT32</type>
      <name>m_confID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a4c999664fb811e6c89aa892296ab3c16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_userID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a7c18ec4a2c7be3f71a19723c34c5e5dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_floorID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>a0061383cab563caf37fb172f3fad886f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_streamID</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>ac743770c7bc55a35bd8f406bbe56b8e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_IsPassive</name>
      <anchorfile>dc/d28/classsampleClient.html</anchorfile>
      <anchor>ae2728bdd4cd369a18b16772bbad0aef0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sampleServer</name>
    <filename>d1/d47/classsampleServer.html</filename>
    <base>BFCP_Server::ServerEvent</base>
    <member kind="function">
      <type></type>
      <name>sampleServer</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>ada73c986f6f454e93ec685b07cadb845</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~sampleServer</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a208e6dde620f06619ea7fc1afc481725</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetConfID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a3dca8e3057f0891fcb6a3852a1cd4f7a</anchor>
      <arglist>(UINT32 p_confID)</arglist>
    </member>
    <member kind="function">
      <type>UINT32</type>
      <name>GetConfID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>aac4ab4ef64f4abbb1ac1a22e3434c42f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUserID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a8ef036139e46ea1bc10b52392d3c6443</anchor>
      <arglist>(UINT16 p_userID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetUserID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>ad070986d81f96e540fb35ce0a5d728cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFloorID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a1062275f56bd9fa1066dace29be27f65</anchor>
      <arglist>(UINT16 p_floorID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetFloorID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a1f3a2f7368e0a921d676c1ea6660851c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStreamID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a86aceac45cb6573d5564dcb7d08413d7</anchor>
      <arglist>(UINT16 p_streamID)</arglist>
    </member>
    <member kind="function">
      <type>UINT16</type>
      <name>GetStreamID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a210fb2e5bc544c72d0abb7b1bde6a919</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetIsPassive</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a0b9f2faf1285f9f4ffa3c31284c4e0a5</anchor>
      <arglist>(bool p_IsServer)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetIsPassive</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a8620298fc0d436652e5f396615eb0799</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFloorctrlMode</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a9b32a2e36d70d625263c5c6e80b0d129</anchor>
      <arglist>(e_floorctrlMode pfloorctrlMode)</arglist>
    </member>
    <member kind="function">
      <type>e_floorctrlMode</type>
      <name>GetFloorctrlMode</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>ac9d07e1a22ef3a0e0435ece518a9d2bf</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>menu</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>ac70fec93d535d5ed6a95071ca00322fe</anchor>
      <arglist>(char *lineptr)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AddUserIDinConf</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>adf1b3bbabde5f6379fcfec6f697c036e</anchor>
      <arglist>(UINT16 p_userID)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RemoveUserIDinConf</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>aa81961532a7f464a54984d4bd242bd19</anchor>
      <arglist>(UINT16 p_userID)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>OnBfcpServerEvent</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>abfc550fff6cc53672b803603b9c81c41</anchor>
      <arglist>(BFCP_fsm::e_BFCP_ACT p_evt, BFCP_fsm::st_BFCP_fsm_event *p_FsmEvent)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Log</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a2565360a452e935e6bf06ab53fddb211</anchor>
      <arglist>(const char *pcFile, int iLine, int iErrorLevel, const char *pcFormat,...)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>OpenServerTcpConnection</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a3ad4ebda6626e8a0f98625221967a812</anchor>
      <arglist>(const char *local_address, int local_port, const char *remote_address, int remote_port, bool isPassive)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BFCP_Server *</type>
      <name>m_BFCP_Server</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a9548d83b238647a140290260438a248e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>e_floorctrlMode</type>
      <name>m_e_floorctrlMode</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a82d06126fb80229455cc83f786b94497</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT32</type>
      <name>m_confID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>ae5a8e15bb38365fd5ac963d5a0255ccc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_userID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a1aa8f455f1495c2837d01542d364a1a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_floorID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>ab174abac6b6ea3012e598307c4a093d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT16</type>
      <name>m_streamID</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>aa68db649aa99040afd76978555d8f467</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_IsPassive</name>
      <anchorfile>d1/d47/classsampleServer.html</anchorfile>
      <anchor>a9ab6a9c62977bfc3f0f32566ee7d5fd0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SessionCondemnedException</name>
    <filename>d0/d0c/classSessionCondemnedException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>SessionCondemnedException</name>
      <anchorfile>d0/d0c/classSessionCondemnedException.html</anchorfile>
      <anchor>aa9e219a95cf5ce8d91d977536d0a5b79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SessionCondemnedException</name>
      <anchorfile>d0/d0c/classSessionCondemnedException.html</anchorfile>
      <anchor>aed4d6ec77739e82e0a28164dc630d15b</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SocketBFCPinputstream</name>
    <filename>d3/d8f/classSocketBFCPinputstream.html</filename>
    <base>BFCPinputstream</base>
    <member kind="function">
      <type></type>
      <name>SocketBFCPinputstream</name>
      <anchorfile>d3/d8f/classSocketBFCPinputstream.html</anchorfile>
      <anchor>a4f22f3a1334b6db95242904f2688b992</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SocketBFCPinputstream</name>
      <anchorfile>d3/d8f/classSocketBFCPinputstream.html</anchorfile>
      <anchor>a413bc593a9dd52c547a5607110b0ef9d</anchor>
      <arglist>(FTCSocket *socket)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SocketBFCPinputstream</name>
      <anchorfile>d3/d8f/classSocketBFCPinputstream.html</anchorfile>
      <anchor>ae35d30c208f2373405bd579a247cd05b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSocket</name>
      <anchorfile>d3/d8f/classSocketBFCPinputstream.html</anchorfile>
      <anchor>afc8ee39f151aa948cf8c5c5495df1464</anchor>
      <arglist>(FTCSocket *socket)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual ssize_t</type>
      <name>readBytes</name>
      <anchorfile>d3/d8f/classSocketBFCPinputstream.html</anchorfile>
      <anchor>a26ee5c2a80717a257eea3edf057a63db</anchor>
      <arglist>(char *buffer, size_t count)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual unsigned long</type>
      <name>availableBytes</name>
      <anchorfile>d3/d8f/classSocketBFCPinputstream.html</anchorfile>
      <anchor>ab5f77eed888abff3afc6f656d3ff8eb5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>FTCSocket *</type>
      <name>m_pSocket</name>
      <anchorfile>d3/d8f/classSocketBFCPinputstream.html</anchorfile>
      <anchor>afd267244a35494639a0cb5959d2d2c78</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SocketBFCPOutputStream</name>
    <filename>d8/dd0/classSocketBFCPOutputStream.html</filename>
    <base>BFCPOutputStream</base>
    <member kind="function">
      <type></type>
      <name>SocketBFCPOutputStream</name>
      <anchorfile>d8/dd0/classSocketBFCPOutputStream.html</anchorfile>
      <anchor>a6fa9524e1393500834cd7a64c9949bea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SocketBFCPOutputStream</name>
      <anchorfile>d8/dd0/classSocketBFCPOutputStream.html</anchorfile>
      <anchor>a2cf73b25ee175e324d7a90734f0bab79</anchor>
      <arglist>(FTCSocket *socket)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SocketBFCPOutputStream</name>
      <anchorfile>d8/dd0/classSocketBFCPOutputStream.html</anchorfile>
      <anchor>af50d04e8cf1c8ad0ca98b83bfbd2b224</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSocket</name>
      <anchorfile>d8/dd0/classSocketBFCPOutputStream.html</anchorfile>
      <anchor>ac25f7cedca33be7359b5624addc4ee43</anchor>
      <arglist>(FTCSocket *socket)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>write</name>
      <anchorfile>d8/dd0/classSocketBFCPOutputStream.html</anchorfile>
      <anchor>a31ff8f0fc8d13818027d3eba414cd454</anchor>
      <arglist>(char b)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>write</name>
      <anchorfile>d8/dd0/classSocketBFCPOutputStream.html</anchorfile>
      <anchor>a588e7c7d24233e1f0d771dda23b804ae</anchor>
      <arglist>(const char *data, unsigned len)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>flush</name>
      <anchorfile>d8/dd0/classSocketBFCPOutputStream.html</anchorfile>
      <anchor>a0aed06b5b2dc130881e087eb0edbf9d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>close</name>
      <anchorfile>d8/dd0/classSocketBFCPOutputStream.html</anchorfile>
      <anchor>ac6c1b7d6168a58516c88070bd63a7dbd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>FTCSocket *</type>
      <name>m_pSocket</name>
      <anchorfile>d8/dd0/classSocketBFCPOutputStream.html</anchorfile>
      <anchor>a2fb8a2da754629986663412d01ab0e0c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>st_bfcp_conference</name>
    <filename>dc/d5a/structst__bfcp__conference.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>bfcp_transport</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>a3af62a2c57c0184556e9d5efcebb86e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_queue *</type>
      <name>pending</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>a5495172a53d3d17d0399a5897c349f8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_queue *</type>
      <name>accepted</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>a50adf193267bb95466b5704fc0e2b3d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_queue *</type>
      <name>granted</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>a4f3440aeac9c436af8edd98b9856b943</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT32</type>
      <name>conferenceID</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>a0e9220daf114ecbcdd6c2cc41a0911d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>floorRequestID</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>a51d64c39015a84f3255875a0202e3783</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_list_users *</type>
      <name>user</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>ac7864ddab02a06e2a2bbc0b672d609a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bfcp_list_floors *</type>
      <name>floor</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>a5ebcebc80fd8bf8aba53acd9302d81bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT32</type>
      <name>chair_wait_request</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>a1b889e83bb36abaf03909346779db429</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>automatic_accepted_deny_policy</name>
      <anchorfile>dc/d5a/structst__bfcp__conference.html</anchorfile>
      <anchor>a71f17835dc36fa7f03bbc0b711a79101</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>st_bfcp_participant_information</name>
    <filename>d9/d1e/structst__bfcp__participant__information.html</filename>
    <member kind="variable">
      <type>UINT32</type>
      <name>conferenceID</name>
      <anchorfile>d9/d1e/structst__bfcp__participant__information.html</anchorfile>
      <anchor>a57bc7084d632a6388e7862a6677596e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>userID</name>
      <anchorfile>d9/d1e/structst__bfcp__participant__information.html</anchorfile>
      <anchor>aeb031d166d613975d83e8ba8d545c984</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>st_bfcp_floors_participant *</type>
      <name>pfloors</name>
      <anchorfile>d9/d1e/structst__bfcp__participant__information.html</anchorfile>
      <anchor>a5eb7aed7959cea7ea9caf593d0749dfe</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>st_bfcp_server</name>
    <filename>dc/d04/structst__bfcp__server.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>bfcp_transport</name>
      <anchorfile>dc/d04/structst__bfcp__server.html</anchorfile>
      <anchor>af9e96d69f90f960edc61e6165b7c20cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>Actual_number_conference</name>
      <anchorfile>dc/d04/structst__bfcp__server.html</anchorfile>
      <anchor>a2f39529c53e061fd4e79dc8e3f25d39f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT16</type>
      <name>Max_number_conference</name>
      <anchorfile>dc/d04/structst__bfcp__server.html</anchorfile>
      <anchor>a4ff98473961acd3861b37823b09b340b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>st_bfcp_conference *</type>
      <name>list_conferences</name>
      <anchorfile>dc/d04/structst__bfcp__server.html</anchorfile>
      <anchor>ab8994f6834ac0462ad8faa3f82835253</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UnknownHostException</name>
    <filename>db/dc4/classUnknownHostException.html</filename>
    <base>BFCPException</base>
    <member kind="function">
      <type></type>
      <name>UnknownHostException</name>
      <anchorfile>db/dc4/classUnknownHostException.html</anchorfile>
      <anchor>a4c2f07cc59d08c438e758d9debf8c475</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UnknownHostException</name>
      <anchorfile>db/dc4/classUnknownHostException.html</anchorfile>
      <anchor>a6243c3ff4e6235017056d65ad688a418</anchor>
      <arglist>(const char *message)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>libbfcp</name>
    <filename>d2/d39/namespacelibbfcp.html</filename>
    <class kind="class">libbfcp::WinShareCtrl</class>
  </compound>
  <compound kind="class">
    <name>libbfcp::WinShareCtrl</name>
    <filename>d0/d61/classlibbfcp_1_1WinShareCtrl.html</filename>
    <member kind="function">
      <type></type>
      <name>WinShareCtrl</name>
      <anchorfile>d0/d61/classlibbfcp_1_1WinShareCtrl.html</anchorfile>
      <anchor>a1acf7f37f0914da65d08d6f6f3115320</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~WinShareCtrl</name>
      <anchorfile>d0/d61/classlibbfcp_1_1WinShareCtrl.html</anchorfile>
      <anchor>a42eb74d624f751ce13fb4eaa44c98459</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>InitializeComponent</name>
      <anchorfile>d0/d61/classlibbfcp_1_1WinShareCtrl.html</anchorfile>
      <anchor>a06f7d7fc3f5f0b08bde22de33646df8b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>System::ComponentModel::Container</type>
      <name>components</name>
      <anchorfile>d0/d61/classlibbfcp_1_1WinShareCtrl.html</anchorfile>
      <anchor>a252492407ec1b82efde7cabca7b15757</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>bfcpcli</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpcli/</path>
    <filename>dir_55ac6989847214f6841d803574fda099.html</filename>
    <file>bfcp_participant.cpp</file>
    <file>bfcp_participant.h</file>
  </compound>
  <compound kind="dir">
    <name>bfcpmsg</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpmsg/</path>
    <filename>dir_cb2c0737bf54bf7e2572ddbdd4fce6ed.html</filename>
    <file>bfcp_messages.c</file>
    <file>bfcp_messages.h</file>
    <file>bfcp_messages_build.c</file>
    <file>bfcp_messages_parse.c</file>
    <file>bfcp_strings.c</file>
    <file>bfcp_strings.h</file>
  </compound>
  <compound kind="dir">
    <name>bfcpsrv</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/bfcpsrv/</path>
    <filename>dir_8f6902d5f767a80dd53c67f128343e47.html</filename>
    <file>bfcp_floor_list.c</file>
    <file>bfcp_floor_list.h</file>
    <file>bfcp_link_list.cpp</file>
    <file>bfcp_link_list.h</file>
    <file>bfcp_server.cpp</file>
    <file>bfcp_server.h</file>
    <file>bfcp_user_list.cpp</file>
    <file>bfcp_user_list.h</file>
  </compound>
  <compound kind="dir">
    <name>bfcpsrvctl</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/bfcpsrvctl/</path>
    <filename>dir_cf662f2fef59a53f0659df4b5fcf98c7.html</filename>
    <dir>bfcpcli</dir>
    <dir>bfcpsrv</dir>
  </compound>
  <compound kind="dir">
    <name>C:</name>
    <path>C:/</path>
    <filename>dir_e6bb53534ac0e427887cf7a94c0c004e.html</filename>
    <dir>Users</dir>
  </compound>
  <compound kind="dir">
    <name>Desktop</name>
    <path>C:/Users/pverney/Desktop/</path>
    <filename>dir_047eb0753c0b073c6d24e09e3a9353b1.html</filename>
    <dir>Dev</dir>
  </compound>
  <compound kind="dir">
    <name>Dev</name>
    <path>C:/Users/pverney/Desktop/Dev/</path>
    <filename>dir_12865e9bf0db93ea26521736a53e0057.html</filename>
    <dir>svn-econf-web</dir>
  </compound>
  <compound kind="dir">
    <name>eConf_v5.1</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/</path>
    <filename>dir_2e3cdbe36c41d14a8d7c29611d8f80b0.html</filename>
    <dir>ftmodules</dir>
  </compound>
  <compound kind="dir">
    <name>ftmmisc</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/</path>
    <filename>dir_e09176eecf0f2b6974249b0fc022884c.html</filename>
    <dir>libbfcp</dir>
  </compound>
  <compound kind="dir">
    <name>ftmodules</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/</path>
    <filename>dir_8813d3b63227dd45ca1ffedad57f8c16.html</filename>
    <dir>ftmmisc</dir>
  </compound>
  <compound kind="dir">
    <name>libbfcp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/</path>
    <filename>dir_48a9062f405a76f256222d87c348bd45.html</filename>
    <dir>bfcpmsg</dir>
    <dir>bfcpsrvctl</dir>
    <dir>samples</dir>
    <file>BFCP_fsm.cpp</file>
    <file>BFCP_fsm.h</file>
    <file>BFCP_porting.h</file>
    <file>BFCP_SDPStrings.h</file>
    <file>bfcp_threads.h</file>
    <file>BFCPapi.cpp</file>
    <file>BFCPapi.h</file>
    <file>BFCPconnection.cpp</file>
    <file>BFCPconnection.h</file>
    <file>BFCPexception.h</file>
    <file>BFCPinputstream.cpp</file>
    <file>BFCPinputstream.h</file>
    <file>BFCPoutputstream.cpp</file>
    <file>BFCPoutputstream.h</file>
    <file>resource.h</file>
    <file>stdafx.cpp</file>
    <file>stdafx.h</file>
    <file>WinShareCtrl.cpp</file>
    <file>WinShareCtrl.h</file>
  </compound>
  <compound kind="dir">
    <name>libbfcp</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/</path>
    <filename>dir_4f12a1e346350243331aacb8fd86a88d.html</filename>
    <dir>libbfcp</dir>
  </compound>
  <compound kind="dir">
    <name>pverney</name>
    <path>C:/Users/pverney/</path>
    <filename>dir_f795dd7e46b941ce2f135056932c6f70.html</filename>
    <dir>Desktop</dir>
  </compound>
  <compound kind="dir">
    <name>samples</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/eConf_v5.1/ftmodules/ftmmisc/libbfcp/libbfcp/samples/</path>
    <filename>dir_b64b4b437d0d99fe712a2aa3de8c7ed5.html</filename>
    <file>client.cpp</file>
    <file>client.h</file>
    <file>server.cpp</file>
    <file>server.h</file>
  </compound>
  <compound kind="dir">
    <name>SDK_src</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/SDK_src/</path>
    <filename>dir_f6b764efe75b6dd3f475957fde5d67e0.html</filename>
    <dir>eConf_v5.1</dir>
  </compound>
  <compound kind="dir">
    <name>svn-econf-web</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/</path>
    <filename>dir_e9dd9a26ed25ca96c05cacbe476ce5a7.html</filename>
    <dir>trunk</dir>
  </compound>
  <compound kind="dir">
    <name>trunk</name>
    <path>C:/Users/pverney/Desktop/Dev/svn-econf-web/trunk/</path>
    <filename>dir_6bf2b60f709ed5298e7a543fd5c009c9.html</filename>
    <dir>SDK_src</dir>
  </compound>
  <compound kind="dir">
    <name>Users</name>
    <path>C:/Users/</path>
    <filename>dir_8ceffd4ee35c3518d4e8bdc7e638efe8.html</filename>
    <dir>pverney</dir>
  </compound>
</tagfile>
