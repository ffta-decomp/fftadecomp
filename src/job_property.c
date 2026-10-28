typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Packed 52-byte record at 0x08521a14. Field names remain selector-based. */
struct JobDefinition {
    u16 p00;
    u8 unknown_at_02[2];
    u8 p01;
    u8 inherit;
    u8 p03;
    u16 p04;
    u16 p05;
    u32 p06 : 4;
    u32 p07 : 4;
    u8 p08;
    u8 p09;
    u8 p10;
    u8 p11;
    u8 p12;
    u8 p13;
    u32 unknown_at_18 : 3;
    u32 p14 : 3;
    u32 p15 : 3;
    u32 p16 : 3;
    u32 p17 : 3;
    u32 p18 : 3;
    u32 p19 : 3;
    u32 p20 : 3;
    u32 p21 : 3;
    u32 unknown_at_21 : 5;
    u8 p22;
    u8 p23;
    u8 p24;
    u8 p25;
    u32 p26 : 12;
    u32 p27 : 12;
    u32 p28 : 12;
    u32 p29 : 12;
    u8 p41;
    u8 p42;
    u8 p43;
    u8 p44;
    u8 p45;
    u8 p46;
    u8 p47;
    u8 unknown_at_27;
    u8 p30;
    u8 p31;
    u8 p32;
    u32 p34 : 4;
    u32 p35 : 4;
    u8 p33;
    u8 p36;
    u8 p37;
    u8 p38;
    u8 p39;
    u8 p40;
    u8 unknown_at_32[2];
} __attribute__((packed));

typedef char JobDefinitionSizeMustBe52[(sizeof(struct JobDefinition) == 52) ? 1 : -1];

extern const struct JobDefinition gJobDefinitions[];

/* Nonzero inheritance redirects. Invalid selectors and cycles intentionally loop. */
#define READ_JOB_PROPERTY(selector, field) \
    case selector: \
        if (job->inherit == 255) \
            job = &gJobDefinitions[fallback_job]; \
        else if (job->inherit != 0) \
            job = &gJobDefinitions[job->inherit]; \
        else \
            return job->field; \
        break

u32 GetJobProperty(u8 job_id, u8 fallback_job, u8 property)
{
    const struct JobDefinition *job = &gJobDefinitions[job_id];

    for (;;) {
        switch (property) {
        READ_JOB_PROPERTY(0, p00);
        READ_JOB_PROPERTY(1, p01);
        case 2: return job->inherit;
        READ_JOB_PROPERTY(3, p03);
        READ_JOB_PROPERTY(4, p04);
        READ_JOB_PROPERTY(5, p05);
        READ_JOB_PROPERTY(6, p06);
        READ_JOB_PROPERTY(7, p07);
        READ_JOB_PROPERTY(8, p08);
        READ_JOB_PROPERTY(9, p09);
        READ_JOB_PROPERTY(10, p10);
        READ_JOB_PROPERTY(11, p11);
        READ_JOB_PROPERTY(12, p12);
        READ_JOB_PROPERTY(13, p13);
        READ_JOB_PROPERTY(14, p14);
        READ_JOB_PROPERTY(15, p15);
        READ_JOB_PROPERTY(16, p16);
        READ_JOB_PROPERTY(17, p17);
        READ_JOB_PROPERTY(18, p18);
        READ_JOB_PROPERTY(19, p19);
        READ_JOB_PROPERTY(20, p20);
        READ_JOB_PROPERTY(21, p21);
        READ_JOB_PROPERTY(22, p22);
        READ_JOB_PROPERTY(23, p23);
        READ_JOB_PROPERTY(24, p24);
        READ_JOB_PROPERTY(25, p25);
        READ_JOB_PROPERTY(26, p26);
        READ_JOB_PROPERTY(27, p27);
        READ_JOB_PROPERTY(28, p28);
        READ_JOB_PROPERTY(29, p29);
        READ_JOB_PROPERTY(30, p30);
        READ_JOB_PROPERTY(31, p31);
        READ_JOB_PROPERTY(32, p32);
        READ_JOB_PROPERTY(34, p34);
        READ_JOB_PROPERTY(35, p35);
        READ_JOB_PROPERTY(33, p33);
        READ_JOB_PROPERTY(36, p36);
        READ_JOB_PROPERTY(37, p37);
        READ_JOB_PROPERTY(38, p38);
        READ_JOB_PROPERTY(39, p39);
        READ_JOB_PROPERTY(40, p40);
        READ_JOB_PROPERTY(41, p41);
        READ_JOB_PROPERTY(42, p42);
        READ_JOB_PROPERTY(43, p43);
        READ_JOB_PROPERTY(44, p44);
        READ_JOB_PROPERTY(45, p45);
        READ_JOB_PROPERTY(46, p46);
        READ_JOB_PROPERTY(47, p47);
        }
    }
}

#undef READ_JOB_PROPERTY
