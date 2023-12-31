//
// Created by Jeremy Cote on 2023-07-29.
//

#include "StatsView.hpp"
#include "StylesManager.hpp"

StatsView::StatsView(lv_obj_t* parent, DataAggregator& aggregator) : View(parent, aggregator) {
    lv_obj_t* container = getContainer();
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_style_set_bg_color(container->styles->style, LV_COLOR_MAKE(255, 128, 128));

    Styles* styles = StylesManager::GetStyles();

    chart = lv_chart_create(container);
    lv_obj_set_layout(chart, LV_LAYOUT_FLEX);
    lv_obj_add_style(chart, styles->GetFullscreenChartStyle(), LV_PART_MAIN);

    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_point_count(chart, 50);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -1000, 3200);


    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 30, 10, 5, 3, true, 20);

    rpmSeries = lv_chart_add_series(chart, LV_COLOR_MAKE(0, 0, 0), 0);

    rpmLabel = lv_label_create(chart);

    auto callback = [this](/*const DataQueue<percentage_t>& rpm, const DataQueue<voltage_t>& voltage*/) {
        lv_chart_set_next_value(chart, rpmSeries, getDataAggregator().throttlePositions.getLatestValue());
        lv_chart_refresh(chart);

        lv_label_set_text_fmt(rpmLabel, "%d RPM", getDataAggregator().throttlePositions.getLatestValue());
    };
    combiner = new CombineLatest(callback, getDataAggregator().throttlePositions, getDataAggregator().batteryVoltages);
//    getDataAggregator().motorVelocities.addListener([this](const DataQueue<velocity_t>& rpm) {
//        lv_chart_set_next_value(chart, rpmSeries, rpm.getLatestValue());
//        lv_chart_refresh(chart);
//
//        lv_label_set_text_fmt(rpmLabel, "%d RPM", rpm.getLatestValue());
//    });
//    getDataAggregator().throttlePositions.addListener([this](const DataQueue<percentage_t>& throttle) {
//        lv_chart_set_next_value(chart, rpmSeries, throttle.getLatestValue());
//        lv_chart_refresh(chart);
//
//        lv_label_set_text_fmt(rpmLabel, "%d RPM", throttle.getLatestValue());
//    });
}

StatsView::~StatsView() {
    delete combiner;
}